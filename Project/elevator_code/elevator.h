/*
 * elevator.h
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

#ifndef RTW_HEADER_elevator_h_
#define RTW_HEADER_elevator_h_
#include <math.h>
#include <string.h>
#ifndef elevator_COMMON_INCLUDES_
# define elevator_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* elevator_COMMON_INCLUDES_ */

#include "elevator_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Delay1;                       /* '<Root>/Delay1' */
} B_elevator_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<Root>/Delay1' */
  real_T direction;                    /* '<Root>/Controller' */
  int32_T sfEvent;                     /* '<Root>/Controller' */
  uint32_T presentTicks;               /* '<Root>/Controller' */
  uint32_T elapsedTicks;               /* '<Root>/Controller' */
  uint32_T previousTicks;              /* '<Root>/Controller' */
  uint16_T temporalCounter_i1;         /* '<Root>/Controller' */
  boolean_T Delay_DSTATE;              /* '<Root>/Delay' */
  int8_T target;                       /* '<Root>/Controller' */
  uint8_T is_c3_elevator;              /* '<Root>/Controller' */
  uint8_T is_FloorButton;              /* '<Root>/Controller' */
  uint8_T is_active_FloorButton;       /* '<Root>/Controller' */
  uint8_T is_Controller;               /* '<Root>/Controller' */
  uint8_T is_active_Controller;        /* '<Root>/Controller' */
  uint8_T is_Normal;                   /* '<Root>/Controller' */
  uint8_T is_Moving;                   /* '<Root>/Controller' */
} DW_elevator_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Controller_Trig_ZCE[8];   /* '<Root>/Controller' */
} PrevZCX_elevator_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T em;                        /* '<Root>/em' */
  boolean_T st;                        /* '<Root>/st' */
  boolean_T b1;                        /* '<Root>/b1' */
  boolean_T b2;                        /* '<Root>/b2' */
  boolean_T b3;                        /* '<Root>/b3' */
  boolean_T b4;                        /* '<Root>/b4' */
  boolean_T b5;                        /* '<Root>/b5' */
  real_T pos;                          /* '<Root>/pos' */
} ExtU_elevator_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T speed;                        /* '<Root>/speed' */
  int8_T f_lamps[5];                   /* '<Root>/f_lamps' */
  boolean_T e_lamp;                    /* '<Root>/e_lamp' */
  boolean_T d_lamp;                    /* '<Root>/d_lamp' */
} ExtY_elevator_T;

/* Parameters (default storage) */
struct P_elevator_T_ {
  real_T Delay1_InitialCondition;      /* Expression: 1
                                        * Referenced by: '<Root>/Delay1'
                                        */
  boolean_T Delay_InitialCondition;/* Computed Parameter: Delay_InitialCondition
                                    * Referenced by: '<Root>/Delay'
                                    */
  boolean_T Constant_Value;            /* Expression: true
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_elevator_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
  } Timing;
};

/* Block parameters (default storage) */
extern P_elevator_T elevator_P;

/* Block signals (default storage) */
extern B_elevator_T elevator_B;

/* Block states (default storage) */
extern DW_elevator_T elevator_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_elevator_T elevator_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_elevator_T elevator_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_elevator_T elevator_Y;

/* Model entry point functions */
extern void elevator_initialize(void);
extern void elevator_step(void);
extern void elevator_terminate(void);

/* Real-time Model object */
extern RT_MODEL_elevator_T *const elevator_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'elevator'
 * '<S1>'   : 'elevator/Controller'
 */
#endif                                 /* RTW_HEADER_elevator_h_ */
