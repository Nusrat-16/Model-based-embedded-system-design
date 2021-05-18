/*
 * elevator_data.c
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

/* Block parameters (default storage) */
P_elevator_T elevator_P = {
  /* Expression: 1
   * Referenced by: '<Root>/Delay1'
   */
  1.0,

  /* Computed Parameter: Delay_InitialCondition
   * Referenced by: '<Root>/Delay'
   */
  0,

  /* Expression: true
   * Referenced by: '<Root>/Constant'
   */
  1
};
