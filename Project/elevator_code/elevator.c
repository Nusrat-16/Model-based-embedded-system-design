/*
 * elevator.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "elevator".
 *
 * Model version              : 1.106
 * Simulink Coder version : 9.3 (R2020a) 18-Nov-2019
 * C source code generated on : Fri Oct 16 15:33:42 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "elevator.h"
#include "elevator_private.h"

/* Named constants for Chart: '<Root>/Controller' */
#define elevator_CALL_EVENT            (-1)
#define elevator_FLOORS                ((int8_T)5)
#define elevator_IN_Break              ((uint8_T)1U)
#define elevator_IN_Buttons            ((uint8_T)1U)
#define elevator_IN_ControlModule      ((uint8_T)1U)
#define elevator_IN_DoorWait           ((uint8_T)1U)
#define elevator_IN_Doors              ((uint8_T)2U)
#define elevator_IN_Emergency          ((uint8_T)1U)
#define elevator_IN_FullSpeed          ((uint8_T)2U)
#define elevator_IN_Idle               ((uint8_T)3U)
#define elevator_IN_Moving             ((uint8_T)4U)
#define elevator_IN_NO_ACTIVE_CHILD    ((uint8_T)0U)
#define elevator_IN_Normal             ((uint8_T)2U)
#define elevator_IN_Plan               ((uint8_T)5U)
#define elevator_LAMP_HERE             ((int8_T)3)
#define elevator_LAMP_OFF              ((int8_T)0)
#define elevator_LAMP_ON               ((int8_T)1)
#define elevator_LAMP_TARGET           ((int8_T)2)
#define elevator_event_B1              (4)
#define elevator_event_B2              (5)
#define elevator_event_B3              (6)
#define elevator_event_B4              (7)
#define elevator_event_B5              (8)
#define elevator_event_Button          (0)
#define elevator_event_Emergency       (2)
#define elevator_event_Start           (3)
#define elevator_event_TIC             (1)

/* Block signals (default storage) */
B_elevator_T elevator_B;

/* Block states (default storage) */
DW_elevator_T elevator_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_elevator_T elevator_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_elevator_T elevator_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_elevator_T elevator_Y;

/* Real-time model */
RT_MODEL_elevator_T elevator_M_;
RT_MODEL_elevator_T *const elevator_M = &elevator_M_;

/* Forward declaration for local functions */
static real_T elevator_ab(real_T x);
static real_T elevator_at_floor(void);
static real_T elevator_look_down(int8_T old_target);
static real_T elevator_look_up(int8_T old_target);
static void elevator_plan(void);
static int8_T elevator_sumlamps(void);
static void elevator_lamp_state(real_T k);
static void elevator_broadcast_Button(void);
static void elevator_c3_elevator(void);
static void elevator_chartstep_c3_elevator(void);

/* Function for Chart: '<Root>/Controller' */
static real_T elevator_ab(real_T x)
{
  return fabs(x);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<Root>/Controller' */
static real_T elevator_at_floor(void)
{
  real_T y;

  /* Update for Inport: '<Root>/pos' */
  y = rt_roundd_snf(elevator_U.pos);
  if (!(fabs(elevator_U.pos - y) < 0.02)) {
    y = -1.0;
  }

  /* End of Update for Inport: '<Root>/pos' */
  return y;
}

/* Function for Chart: '<Root>/Controller' */
static real_T elevator_look_down(int8_T old_target)
{
  real_T no;
  real_T next_floor;
  int32_T k;
  int8_T tmp;
  real_T tmp_0;
  int32_T tmp_1;
  boolean_T exitg1;

  /* Update for Inport: '<Root>/pos' */
  next_floor = fmax(floor(elevator_U.pos - 0.5), 1.0);
  no = 1.0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= (int32_T)next_floor - 1)) {
    tmp_0 = (next_floor + 1.0) - ((real_T)k + 1.0);
    if (tmp_0 < 128.0) {
      if (tmp_0 >= -128.0) {
        tmp = (int8_T)tmp_0;
      } else {
        tmp = MIN_int8_T;
      }
    } else {
      tmp = MAX_int8_T;
    }

    tmp_1 = tmp - 1;
    if ((elevator_Y.f_lamps[tmp_1] == 1) || (elevator_Y.f_lamps[tmp_1] == 2)) {
      if (old_target > 0) {
        k = old_target - 1;
        if (elevator_Y.f_lamps[k] == 2) {
          elevator_Y.f_lamps[k] = elevator_LAMP_ON;
        }
      }

      elevator_Y.f_lamps[tmp_1] = elevator_LAMP_TARGET;
      elevator_DW.target = tmp;
      if (elevator_DW.target != elevator_at_floor()) {
        elevator_DW.direction = -1.0;
      }

      no = 0.0;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return no;
}

/* Function for Chart: '<Root>/Controller' */
static real_T elevator_look_up(int8_T old_target)
{
  real_T no;
  int8_T k;
  real_T x;
  int32_T tmp;
  int32_T tmp_0;
  boolean_T exitg1;

  /* Update for Inport: '<Root>/pos' */
  x = ceil(elevator_U.pos + 0.5);
  no = 1.0;
  if (rtIsNaN(x) || (x > 5.0)) {
    k = elevator_FLOORS;
  } else if (x < 128.0) {
    if (x >= -128.0) {
      k = (int8_T)x;
    } else {
      k = MIN_int8_T;
    }
  } else {
    k = MAX_int8_T;
  }

  exitg1 = false;
  while ((!exitg1) && (k < 6)) {
    tmp = k - 1;
    if ((elevator_Y.f_lamps[tmp] == 1) || (elevator_Y.f_lamps[tmp] == 2)) {
      if (old_target > 0) {
        tmp_0 = old_target - 1;
        if (elevator_Y.f_lamps[tmp_0] == 2) {
          elevator_Y.f_lamps[tmp_0] = elevator_LAMP_ON;
        }
      }

      elevator_Y.f_lamps[tmp] = elevator_LAMP_TARGET;
      elevator_DW.target = k;
      if (elevator_DW.target != elevator_at_floor()) {
        elevator_DW.direction = 1.0;
      }

      no = 0.0;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return no;
}

/* Function for Chart: '<Root>/Controller' */
static void elevator_plan(void)
{
  int8_T old_target;
  real_T d;
  old_target = elevator_DW.target;
  if (elevator_DW.direction > 0.0) {
    d = elevator_look_up(elevator_DW.target);
    if (d != 0.0) {
      d = elevator_look_down(old_target);
      if (d != 0.0) {
        elevator_DW.direction = 0.0;
        elevator_DW.target = -1;
      }
    }
  } else {
    d = elevator_look_down(elevator_DW.target);
    if (d != 0.0) {
      d = elevator_look_up(old_target);
      if (d != 0.0) {
        elevator_DW.direction = 0.0;
        elevator_DW.target = -1;
      }
    }
  }
}

/* Function for Chart: '<Root>/Controller' */
static int8_T elevator_sumlamps(void)
{
  int32_T tmp;

  /* Outport: '<Root>/f_lamps' */
  tmp = elevator_Y.f_lamps[0] + elevator_Y.f_lamps[1];
  if (tmp > 127) {
    tmp = 127;
  } else {
    if (tmp < -128) {
      tmp = -128;
    }
  }

  /* Outport: '<Root>/f_lamps' */
  tmp += elevator_Y.f_lamps[2];
  if (tmp > 127) {
    tmp = 127;
  } else {
    if (tmp < -128) {
      tmp = -128;
    }
  }

  /* Outport: '<Root>/f_lamps' */
  tmp += elevator_Y.f_lamps[3];
  if (tmp > 127) {
    tmp = 127;
  } else {
    if (tmp < -128) {
      tmp = -128;
    }
  }

  /* Outport: '<Root>/f_lamps' */
  tmp += elevator_Y.f_lamps[4];
  if (tmp > 127) {
    tmp = 127;
  } else {
    if (tmp < -128) {
      tmp = -128;
    }
  }

  return (int8_T)tmp;
}

/* Function for Chart: '<Root>/Controller' */
static void elevator_lamp_state(real_T k)
{
  int32_T tmp;
  tmp = (int32_T)k - 1;

  /* Outport: '<Root>/f_lamps' */
  if (elevator_Y.f_lamps[tmp] == 0) {
    elevator_Y.f_lamps[tmp] = elevator_LAMP_ON;
  }

  /* End of Outport: '<Root>/f_lamps' */
}

/* Function for Chart: '<Root>/Controller' */
static void elevator_broadcast_Button(void)
{
  int32_T b_previousEvent;
  b_previousEvent = elevator_DW.sfEvent;
  elevator_DW.sfEvent = elevator_event_Button;

  /* Chart: '<Root>/Controller' */
  elevator_c3_elevator();
  elevator_DW.sfEvent = b_previousEvent;
}

/* Function for Chart: '<Root>/Controller' */
static void elevator_c3_elevator(void)
{
  boolean_T guard1 = false;
  if (elevator_DW.is_c3_elevator == 1) {
    if (elevator_DW.is_active_Controller != 0U) {
      guard1 = false;
      switch (elevator_DW.is_Controller) {
       case elevator_IN_Emergency:
        /* Outport: '<Root>/d_lamp' incorporates:
         *  Outport: '<Root>/e_lamp'
         *  Outport: '<Root>/f_lamps'
         *  Outport: '<Root>/speed'
         */
        if ((elevator_DW.sfEvent == elevator_event_Emergency) &&
            (!elevator_Y.d_lamp)) {
          elevator_Y.e_lamp = false;
          elevator_DW.is_Controller = elevator_IN_Normal;
          elevator_DW.is_Normal = elevator_IN_Idle;
          elevator_Y.speed = 0.0;
        } else {
          if ((elevator_DW.sfEvent == elevator_event_Emergency) &&
              elevator_Y.d_lamp) {
            elevator_Y.e_lamp = false;
            elevator_DW.is_Controller = elevator_IN_Normal;
            elevator_DW.is_Normal = elevator_IN_Doors;
            elevator_DW.temporalCounter_i1 = 0U;
            elevator_Y.f_lamps[elevator_DW.target - 1] = elevator_LAMP_HERE;
            elevator_Y.d_lamp = true;
          }
        }
        break;

       case elevator_IN_Normal:
        if ((elevator_DW.sfEvent == elevator_event_Emergency) || (elevator_ab
             (elevator_U.pos - elevator_B.Delay1) > 0.1)) {
          elevator_DW.is_Moving = elevator_IN_NO_ACTIVE_CHILD;
          elevator_DW.is_Normal = elevator_IN_NO_ACTIVE_CHILD;
          elevator_DW.is_Controller = elevator_IN_Emergency;

          /* Outport: '<Root>/e_lamp' */
          elevator_Y.e_lamp = true;

          /* Outport: '<Root>/speed' */
          elevator_Y.speed = 0.0;
        } else {
          switch (elevator_DW.is_Normal) {
           case elevator_IN_DoorWait:
            if (elevator_DW.temporalCounter_i1 >= 500U) {
              elevator_DW.is_Normal = elevator_IN_Doors;
              elevator_DW.temporalCounter_i1 = 0U;

              /* Outport: '<Root>/f_lamps' */
              elevator_Y.f_lamps[elevator_DW.target - 1] = elevator_LAMP_HERE;

              /* Outport: '<Root>/d_lamp' */
              elevator_Y.d_lamp = true;
            }
            break;

           case elevator_IN_Doors:
            if (elevator_DW.temporalCounter_i1 >= 5000U) {
              /* Outport: '<Root>/d_lamp' */
              elevator_Y.d_lamp = false;

              /* Outport: '<Root>/f_lamps' */
              elevator_Y.f_lamps[elevator_DW.target - 1] = elevator_LAMP_OFF;
              elevator_DW.is_Normal = elevator_IN_Plan;
              elevator_plan();

              /* Outport: '<Root>/speed' */
              elevator_Y.speed = elevator_DW.direction;
            }
            break;

           case elevator_IN_Idle:
            if (elevator_DW.sfEvent == elevator_event_Button) {
              guard1 = true;
            } else if (elevator_Y.d_lamp) {
              elevator_DW.is_Normal = elevator_IN_Doors;
              elevator_DW.temporalCounter_i1 = 0U;

              /* Outport: '<Root>/f_lamps' */
              elevator_Y.f_lamps[elevator_DW.target - 1] = elevator_LAMP_HERE;

              /* Outport: '<Root>/d_lamp' */
              elevator_Y.d_lamp = true;
            } else {
              if (elevator_sumlamps() > 0) {
                guard1 = true;
              }
            }
            break;

           case elevator_IN_Moving:
            if (elevator_at_floor() == elevator_DW.target) {
              elevator_DW.is_Moving = elevator_IN_NO_ACTIVE_CHILD;

              /* Outport: '<Root>/speed' */
              elevator_Y.speed = 0.0;
              elevator_DW.is_Normal = elevator_IN_DoorWait;
              elevator_DW.temporalCounter_i1 = 0U;
            } else {
              switch (elevator_DW.is_Moving) {
               case elevator_IN_Break:
                /* Outport: '<Root>/speed' incorporates:
                 *  Inport: '<Root>/pos'
                 */
                elevator_Y.speed = (real_T)elevator_DW.target - elevator_U.pos;
                break;

               case elevator_IN_FullSpeed:
                /* Update for Inport: '<Root>/pos' */
                if (elevator_ab(elevator_U.pos - (real_T)elevator_DW.target) <
                    0.4) {
                  elevator_DW.is_Moving = elevator_IN_Break;
                } else {
                  if (elevator_DW.sfEvent == elevator_event_Button) {
                    elevator_DW.is_Moving = elevator_IN_NO_ACTIVE_CHILD;
                    elevator_DW.is_Normal = elevator_IN_Plan;
                    elevator_plan();

                    /* Outport: '<Root>/speed' */
                    elevator_Y.speed = elevator_DW.direction;
                  }
                }
                break;

               default:
                /* Unreachable state, for coverage only */
                elevator_DW.is_Moving = elevator_IN_NO_ACTIVE_CHILD;
                break;
              }
            }
            break;

           case elevator_IN_Plan:
            if (elevator_DW.target < 1) {
              elevator_DW.is_Normal = elevator_IN_Idle;

              /* Outport: '<Root>/speed' */
              elevator_Y.speed = 0.0;
            } else if (elevator_at_floor() != elevator_DW.target) {
              elevator_DW.is_Normal = elevator_IN_Moving;
              elevator_DW.is_Moving = elevator_IN_FullSpeed;
            } else {
              if ((elevator_at_floor() == elevator_DW.target) &&
                  (elevator_Y.speed == 0.0)) {
                elevator_DW.is_Normal = elevator_IN_Doors;
                elevator_DW.temporalCounter_i1 = 0U;

                /* Outport: '<Root>/f_lamps' */
                elevator_Y.f_lamps[elevator_DW.target - 1] = elevator_LAMP_HERE;

                /* Outport: '<Root>/d_lamp' */
                elevator_Y.d_lamp = true;
              }
            }
            break;

           default:
            /* Unreachable state, for coverage only */
            elevator_DW.is_Normal = elevator_IN_NO_ACTIVE_CHILD;
            break;
          }
        }
        break;

       default:
        /* Unreachable state, for coverage only */
        elevator_DW.is_Controller = elevator_IN_NO_ACTIVE_CHILD;
        break;
      }

      if (guard1) {
        elevator_DW.is_Normal = elevator_IN_Plan;
        elevator_plan();

        /* Outport: '<Root>/speed' */
        elevator_Y.speed = elevator_DW.direction;
      }
    }

    if ((elevator_DW.is_active_FloorButton != 0U) && (elevator_DW.is_FloorButton
         == 1)) {
      if (elevator_DW.sfEvent == elevator_event_B1) {
        elevator_DW.is_FloorButton = elevator_IN_NO_ACTIVE_CHILD;
        elevator_lamp_state(1.0);
        elevator_broadcast_Button();
        if ((elevator_DW.is_FloorButton == 0) &&
            (elevator_DW.is_active_FloorButton != 0U)) {
          elevator_DW.is_FloorButton = elevator_IN_Buttons;
        }
      } else if (elevator_DW.sfEvent == elevator_event_B2) {
        elevator_DW.is_FloorButton = elevator_IN_NO_ACTIVE_CHILD;
        elevator_lamp_state(2.0);
        elevator_broadcast_Button();
        if ((elevator_DW.is_FloorButton == 0) &&
            (elevator_DW.is_active_FloorButton != 0U)) {
          elevator_DW.is_FloorButton = elevator_IN_Buttons;
        }
      } else if (elevator_DW.sfEvent == elevator_event_B3) {
        elevator_DW.is_FloorButton = elevator_IN_NO_ACTIVE_CHILD;
        elevator_lamp_state(3.0);
        elevator_broadcast_Button();
        if ((elevator_DW.is_FloorButton == 0) &&
            (elevator_DW.is_active_FloorButton != 0U)) {
          elevator_DW.is_FloorButton = elevator_IN_Buttons;
        }
      } else if (elevator_DW.sfEvent == elevator_event_B4) {
        elevator_DW.is_FloorButton = elevator_IN_NO_ACTIVE_CHILD;
        elevator_lamp_state(4.0);
        elevator_broadcast_Button();
        if ((elevator_DW.is_FloorButton == 0) &&
            (elevator_DW.is_active_FloorButton != 0U)) {
          elevator_DW.is_FloorButton = elevator_IN_Buttons;
        }
      } else {
        if (elevator_DW.sfEvent == elevator_event_B5) {
          elevator_DW.is_FloorButton = elevator_IN_NO_ACTIVE_CHILD;
          elevator_lamp_state(5.0);
          elevator_broadcast_Button();
          if ((elevator_DW.is_FloorButton == 0) &&
              (elevator_DW.is_active_FloorButton != 0U)) {
            elevator_DW.is_FloorButton = elevator_IN_Buttons;
          }
        }
      }
    }
  }
}

/* Function for Chart: '<Root>/Controller' */
static void elevator_chartstep_c3_elevator(void)
{
  elevator_c3_elevator();
}

/* Model step function */
void elevator_step(void)
{
  boolean_T rtb_LogicalOperator;
  boolean_T zcEvent[8];
  int8_T rtb_inputevents[8];
  int32_T i;
  boolean_T zcEvent_0;

  /* Delay: '<Root>/Delay1' */
  elevator_B.Delay1 = elevator_DW.Delay1_DSTATE;

  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Constant: '<Root>/Constant'
   *  Delay: '<Root>/Delay'
   */
  rtb_LogicalOperator = elevator_DW.Delay_DSTATE ^ elevator_P.Constant_Value;

  /* Chart: '<Root>/Controller' incorporates:
   *  TriggerPort: '<S1>/input events'
   */
  zcEvent[0] = (rtb_LogicalOperator && (elevator_PrevZCX.Controller_Trig_ZCE[0]
    != POS_ZCSIG));

  /* Inport: '<Root>/em' */
  zcEvent[1] = (elevator_U.em && (elevator_PrevZCX.Controller_Trig_ZCE[1] !=
    POS_ZCSIG));

  /* Inport: '<Root>/st' */
  zcEvent[2] = (elevator_U.st && (elevator_PrevZCX.Controller_Trig_ZCE[2] !=
    POS_ZCSIG));

  /* Inport: '<Root>/b1' */
  zcEvent[3] = (elevator_U.b1 && (elevator_PrevZCX.Controller_Trig_ZCE[3] !=
    POS_ZCSIG));

  /* Inport: '<Root>/b2' */
  zcEvent[4] = (elevator_U.b2 && (elevator_PrevZCX.Controller_Trig_ZCE[4] !=
    POS_ZCSIG));

  /* Inport: '<Root>/b3' */
  zcEvent[5] = (elevator_U.b3 && (elevator_PrevZCX.Controller_Trig_ZCE[5] !=
    POS_ZCSIG));

  /* Inport: '<Root>/b4' */
  zcEvent[6] = (elevator_U.b4 && (elevator_PrevZCX.Controller_Trig_ZCE[6] !=
    POS_ZCSIG));

  /* Inport: '<Root>/b5' */
  zcEvent[7] = (elevator_U.b5 && (elevator_PrevZCX.Controller_Trig_ZCE[7] !=
    POS_ZCSIG));
  zcEvent_0 = false;
  for (i = 0; i < 8; i++) {
    zcEvent_0 = (zcEvent_0 || zcEvent[i]);
  }

  if (zcEvent_0) {
    for (i = 0; i < 8; i++) {
      rtb_inputevents[i] = (int8_T)zcEvent[i];
    }

    elevator_DW.presentTicks = elevator_M->Timing.clockTick0;
    elevator_DW.elapsedTicks = elevator_DW.presentTicks -
      elevator_DW.previousTicks;
    elevator_DW.previousTicks = elevator_DW.presentTicks;
    if (elevator_DW.temporalCounter_i1 + elevator_DW.elapsedTicks <= 8191U) {
      elevator_DW.temporalCounter_i1 = (uint16_T)(elevator_DW.temporalCounter_i1
        + elevator_DW.elapsedTicks);
    } else {
      elevator_DW.temporalCounter_i1 = 8191U;
    }

    if (rtb_inputevents[0U] == 1) {
      elevator_DW.sfEvent = elevator_event_TIC;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[1U] == 1) {
      elevator_DW.sfEvent = elevator_event_Emergency;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[2U] == 1) {
      elevator_DW.sfEvent = elevator_event_Start;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[3U] == 1) {
      elevator_DW.sfEvent = elevator_event_B1;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[4U] == 1) {
      elevator_DW.sfEvent = elevator_event_B2;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[5U] == 1) {
      elevator_DW.sfEvent = elevator_event_B3;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[6U] == 1) {
      elevator_DW.sfEvent = elevator_event_B4;
      elevator_chartstep_c3_elevator();
    }

    if (rtb_inputevents[7U] == 1) {
      elevator_DW.sfEvent = elevator_event_B5;
      elevator_chartstep_c3_elevator();
    }
  }

  elevator_PrevZCX.Controller_Trig_ZCE[0] = rtb_LogicalOperator;

  /* Inport: '<Root>/em' */
  elevator_PrevZCX.Controller_Trig_ZCE[1] = elevator_U.em;

  /* Inport: '<Root>/st' */
  elevator_PrevZCX.Controller_Trig_ZCE[2] = elevator_U.st;

  /* Inport: '<Root>/b1' */
  elevator_PrevZCX.Controller_Trig_ZCE[3] = elevator_U.b1;

  /* Inport: '<Root>/b2' */
  elevator_PrevZCX.Controller_Trig_ZCE[4] = elevator_U.b2;

  /* Inport: '<Root>/b3' */
  elevator_PrevZCX.Controller_Trig_ZCE[5] = elevator_U.b3;

  /* Inport: '<Root>/b4' */
  elevator_PrevZCX.Controller_Trig_ZCE[6] = elevator_U.b4;

  /* Inport: '<Root>/b5' */
  elevator_PrevZCX.Controller_Trig_ZCE[7] = elevator_U.b5;

  /* Update for Delay: '<Root>/Delay1' incorporates:
   *  Inport: '<Root>/pos'
   */
  elevator_DW.Delay1_DSTATE = elevator_U.pos;

  /* Update for Delay: '<Root>/Delay' */
  elevator_DW.Delay_DSTATE = rtb_LogicalOperator;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  elevator_M->Timing.clockTick0++;
  if (!elevator_M->Timing.clockTick0) {
    elevator_M->Timing.clockTickH0++;
  }
}

/* Model initialize function */
void elevator_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)elevator_M, 0,
                sizeof(RT_MODEL_elevator_T));

  /* block I/O */
  (void) memset(((void *) &elevator_B), 0,
                sizeof(B_elevator_T));

  /* states (dwork) */
  (void) memset((void *)&elevator_DW, 0,
                sizeof(DW_elevator_T));

  /* external inputs */
  (void)memset(&elevator_U, 0, sizeof(ExtU_elevator_T));

  /* external outputs */
  (void) memset((void *)&elevator_Y, 0,
                sizeof(ExtY_elevator_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      elevator_PrevZCX.Controller_Trig_ZCE[i] = POS_ZCSIG;
    }
  }

  {
    int32_T i;

    /* InitializeConditions for Delay: '<Root>/Delay1' */
    elevator_DW.Delay1_DSTATE = elevator_P.Delay1_InitialCondition;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    elevator_DW.Delay_DSTATE = elevator_P.Delay_InitialCondition;

    /* SystemInitialize for Chart: '<Root>/Controller' */
    elevator_DW.temporalCounter_i1 = 0U;
    elevator_DW.is_Moving = elevator_IN_NO_ACTIVE_CHILD;
    elevator_DW.target = -1;
    elevator_DW.direction = 0.0;
    for (i = 0; i < 5; i++) {
      /* SystemInitialize for Outport: '<Root>/f_lamps' incorporates:
       *  Chart: '<Root>/Controller'
       */
      elevator_Y.f_lamps[i] = 0;
    }

    /* SystemInitialize for Outport: '<Root>/e_lamp' incorporates:
     *  Chart: '<Root>/Controller'
     */
    elevator_Y.e_lamp = false;

    /* SystemInitialize for Outport: '<Root>/d_lamp' incorporates:
     *  Chart: '<Root>/Controller'
     */
    elevator_Y.d_lamp = false;

    /* SystemInitialize for Chart: '<Root>/Controller' */
    elevator_DW.presentTicks = 0U;
    elevator_DW.elapsedTicks = 0U;
    elevator_DW.previousTicks = 0U;
    elevator_DW.sfEvent = elevator_CALL_EVENT;

    /* Chart: '<Root>/Controller' */
    elevator_DW.is_c3_elevator = elevator_IN_ControlModule;
    elevator_DW.is_active_Controller = 1U;
    elevator_DW.is_Controller = elevator_IN_Normal;
    elevator_DW.is_Normal = elevator_IN_Idle;

    /* Outport: '<Root>/speed' incorporates:
     *  Chart: '<Root>/Controller'
     * */
    elevator_Y.speed = 0.0;

    /* Chart: '<Root>/Controller' */
    elevator_DW.is_active_FloorButton = 1U;
    elevator_DW.is_FloorButton = elevator_IN_Buttons;
  }

  /* Enable for Chart: '<Root>/Controller' */
  elevator_DW.presentTicks = elevator_M->Timing.clockTick0;
  elevator_DW.previousTicks = elevator_DW.presentTicks;
}

/* Model terminate function */
void elevator_terminate(void)
{
  /* (no terminate code required) */
}
