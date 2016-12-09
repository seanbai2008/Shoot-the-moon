#include "Shoot_the_moon.h"

#define Pi 3.1415926
#define pulley_diameter 43.942
#define rod_length 490
#define total_steps 400
#define step_per_angle 0.0157

#define COILA_PHASE 8
#define COILA_ENABLE 9
#define COILB_PHASE  10
#define COILB_ENABLE 11



//pluto_tre
// float traj_ref[300]= {0.0469386,0.0467345,0.0465326,0.0463327,0.0461347,0.0459388,0.0457447,0.0455525,0.0453622,0.0451737,0.0449869,0.0448019,0.0446186,0.0444371,0.0442571,0.0440788,0.0439022,0.043727,0.0435535,0.0433815,0.043211,0.0430419,0.0428744,0.0427082,0.0425435,0.0423802,0.0422182,0.0420577,0.0418984,0.0417405,0.0415838,0.0414285,0.0412744,0.0411216,0.04097,0.0408196,0.0406704,0.0405224,0.0403756,0.0402299,0.0400853,0.0399419,0.0397996,0.0396584,0.0395182,0.0393792,0.0392412,0.0391042,0.0389683,0.0388334,0.0386995,0.0385666,0.0384347,0.0383037,0.0381738,0.0380447,0.0379167,0.0377895,0.0376633,0.037538,0.0374135,0.03729,0.0371674,0.0370456,0.0369247,0.0368046,0.0366854,0.036567,0.0364495,0.0363327,0.0362168,0.0361017,0.0359874,0.0358738,0.035761,0.035649,0.0355378,0.0354273,0.0353176,0.0352086,0.0351003,0.0349928,0.034886,0.0347799,0.0346745,0.0345698,0.0344658,0.0343624,0.0342598,0.0341578,0.0340565,0.0339559,0.0338559,0.0337565,0.0336578,0.0335597,0.0334623,0.0333655,0.0332693,0.0331737,0.0330787,0.0329843,0.0328905,0.0327973,0.0327047,0.0326127,0.0325212,0.0324304,0.03234,0.0322503,0.0321611,0.0320724,0.0319843,0.0318968,0.0318098,0.0317233,0.0316373,0.0315519,0.031467,0.0313826,0.0312987,0.0312153,0.0311324,0.03105,0.0309681,0.0308867,0.0308058,0.0307254,0.0306455,0.030566,0.030487,0.0304084,0.0303304,0.0302527,0.0301756,0.0300989,0.0300226,0.0299468,0.0298715,0.0297965,0.029722,0.029648,0.0295743,0.0295011,0.0294284,0.029356,0.0292841,0.0292125,0.0291414,0.0290707,0.0290004,0.0289304,0.0288609,0.0287918,0.0287231,0.0286547,0.0285868,0.0285192,0.028452,0.0283852,0.0283188,0.0282527,0.0281871,0.0281217,0.0280568,0.0279922,0.0279279,0.0278641,0.0278006,0.0277374,0.0276746,0.0276121,0.02755,0.0274882,0.0274268,0.0273657,0.0273049,0.0272445,0.0271844,0.0271246,0.0270652,0.027006,0.0269472,0.0268888,0.0268306,0.0267728,0.0267153,0.0266581,0.0266012,0.0265446,0.0264883,0.0264323,0.0263767,0.0263213,0.0262662,0.0262115,0.026157,0.0261028,0.0260489,0.0259953,0.025942,0.025889,0.0258363,0.0257838,0.0257316,0.0256798,0.0256282,0.0255768,0.0255258,0.025475,0.0254245,0.0253742,0.0253243,0.0252746,0.0252251,0.025176,0.0251271,0.0250784,0.02503,0.0249819,0.024934,0.0248864,0.0248391,0.024792,0.0247451,0.0246985,0.0246522,0.0246061,0.0245602,0.0245146,0.0244693,0.0244241,0.0243793,0.0243346,0.0242902,0.0242461,0.0242021,0.0241585,0.024115,0.0240718,0.0240288,0.023986,0.0239435,0.0239012,0.0238592,0.0238173,0.0237757,0.0237343,0.0236931,0.0236522,0.0236115,0.023571,0.0235307,0.0234906,0.0234508,0.0234111,0.0233717,0.0233325,0.0232935,0.0232547,0.0232162,0.0231778,0.0231397,0.0231018,0.023064,0.0230265,0.0229892,0.0229521,0.0229152,0.0228785,0.022842,0.0228057,0.0227696,0.0227337,0.022698,0.0226625,0.0226272,0.0225921,0.0225572,0.0225225,0.022488,0.0224537,0.0224195,0.0223856,0.0223519,0.0223183,0.022285,0.0222518,0.0222188,0.022186,0.0221534,0.022121,0.0220888,0.0220567,0.0220248,0.0219932,0.0219617,0.0219304,0.0218992,0.0218683,};

void motor::motor_init(){

  digitalWrite(COILA_PHASE, HIGH);
  digitalWrite(COILB_PHASE, HIGH);
  digitalWrite(COILA_ENABLE, HIGH);
  digitalWrite(COILB_ENABLE, HIGH);

}

void motor::initialize_position(int16_t inital_steps){

    while(inital_steps--){
      move(1);
      delay(3); //3 millis is the least duration between each state so that
                //the motor can rotate without losing steps
    }
}


void motor::make_single_backward_step(){
  // Serial.println(current_steps);
  // Serial.println(current_steps%8);
  switch(current_steps%8){
    case 0:
      digitalWrite(COILA_PHASE, HIGH);
      digitalWrite(COILB_PHASE, HIGH);
      digitalWrite(COILA_ENABLE, HIGH);
      digitalWrite(COILB_ENABLE, HIGH);
      current_steps++;
    break;

    case 1:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, LOW);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps++;
    break;

    case 2:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps++;
    break;

    case 3:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, LOW);
    current_steps++;
    break;
    case 4:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps++;
    break;
    case 5:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, LOW);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps++;
    break;
    case 6:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps++;
    break;
    case 7:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, LOW);
    current_steps++;
    break;
  }
  if (current_steps == 400) current_steps =0;
  // Serial.println(current_steps);
  // Serial.println(current_steps%8);
  // Serial.println();
}

void motor::make_single_forward_step(){
  // Serial.println(current_steps);
  // Serial.println(current_steps%8);
  switch(current_steps%8){
    case 2:
      digitalWrite(COILA_PHASE, HIGH);
      digitalWrite(COILB_PHASE, HIGH);
      digitalWrite(COILA_ENABLE, HIGH);
      digitalWrite(COILB_ENABLE, HIGH);
      current_steps--;
    break;

    case 3:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, LOW);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps--;
    break;

    case 4:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps--;
    break;

    case 5:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, LOW);
    current_steps--;
    break;
    case 6:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps--;
    break;
    case 7:
    digitalWrite(COILA_PHASE, LOW);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, LOW);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps--;
    break;
    case 0:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, LOW);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, HIGH);
    current_steps--;
    break;
    case 1:
    digitalWrite(COILA_PHASE, HIGH);
    digitalWrite(COILB_PHASE, HIGH);
    digitalWrite(COILA_ENABLE, HIGH);
    digitalWrite(COILB_ENABLE, LOW);
    current_steps--;
    break;
  }
  if (current_steps == -1) current_steps =399;
  // Serial.println(current_steps);
  // Serial.println(current_steps%8);
  // Serial.println();
}


void motor::move(int16_t steps){
  // Serial.println(current_steps);
    if(steps>0){
      if (current_steps>the_most_leftest_position){
        while(steps--){
          make_single_forward_step();
        }
      }
    }
    else if(steps<0){
      steps =-steps;
      if (current_steps<the_most_rightest_position){
        while(steps--){
          make_single_backward_step();
        }
      }
    }
}

float motor::angle_to_position(float ref_angle){
  float pulley_angle = ref_angle*rod_length/(pulley_diameter/2);
  int16_t steps = (int16_t)(pulley_angle/step_per_angle);
  return steps;
}
