/*-----------------------------------*/
/*             >>>Pico<<<            */
/*            Theo D'Hondt           */
/*   VUB Programming Technology Lab  */
/*             (c) 1997              */
/*-----------------------------------*/

/*------------------------------------------------------------------------*/
/*   _DO_ESCAPE_  ->  escape requested                                    */
/*   _DO_ACCEPT_  ->  accept requested                                    */
/*   _PICO_DONE_  ->  done                                                */
/*   _AGR_ERROR_  ->  abstract grammar violation                          */
/*   _ATC_ERROR_  ->  argument type conflict                              */
/*   _BUF_ERROR_  ->  text buffer overflow                                */
/*   _CTL_ERROR_  ->  control violation                                   */
/*   _DCT_ERROR_  ->  too many names                                      */
/*   _DIG_ERROR_  ->  digit required                                      */
/*   _DPS_ERROR_  ->  duplicate session identifier                        */
/*   _EXP_ERROR_  ->  expression violation                                */
/*   _EXT_ERROR_  ->  excess token(s)                                     */
/*   _IAG_ERROR_  ->  invalid argument                                    */
/*   _IDX_ERROR_  ->  table index violation                               */
/*   _IIX_ERROR_  ->  invalid index                                       */
/*   _ILL_ERROR_  ->  illegal character                                   */
/*   _INF_ERROR_  ->  infinite value                                      */
/*   _IPM_ERROR_  ->  invalid parameter                                   */
/*   _MEM_ERROR_  ->  storage overflow                                    */
/*   _NAB_ERROR_  ->  not a boolean                                       */
/*   _NAF_ERROR_  ->  not a function+                                     */
/*   _NAT_ERROR_  ->  not a table                                         */
/*   _NBR_ERROR_  ->  number too large                                    */
/*   _NEG_ERROR_  ->  negative argument                                   */
/*   _NMA_ERROR_  ->  non-matching argument list                          */
/*   _RBC_ERROR_  ->  right brace expected                                */
/*   _RBR_ERROR_  ->  right bracket expected                              */
/*   _REE_ERROR_  ->  reentrancy violation                                */
/*   _REF_ERROR_  ->  reference expected                                  */
/*   _RNG_ERROR_  ->  range error                                         */
/*   _RPR_ERROR_  ->  right parenthesis expected                          */
/*   _SIZ_ERROR_  ->  invalid size                                        */
/*   _SNA_ERROR_  ->  session not active                                  */
/*   _STK_ERROR_  ->  stack error                                         */
/*   _TAG_ERROR_  ->  invalid tag                                         */
/*   _TMS_ERROR_  ->  too many sessions                                   */
/*   _TXT_ERROR_  ->  non-terminated text                                 */
/*   _UDI_ERROR_  ->  undefined identifier                                */
/*   _USR_ERROR_  ->  user error                                          */
/*   _ZDV_ERROR_  ->  zero division                                       */
/*   _APL_ERROR_  ->  application expected                                */
/*   _TQA_ERROR_  ->  thread request/answer expected                      */
/*   _RTH_ERROR_  ->  right thread parentheses expected                   */
/*   _RTS_ERROR_  ->  right thread brace expected                         */
/*   _THR_ERROR_  ->  thread expected                                     */
/*   _TNF_ERROR_  ->  thread not found                                    */
/*------------------------------------------------------------------------*/

/* public types */

typedef          void   _NIL_TYPE_;
typedef          void * _ADR_TYPE_;
typedef unsigned long   _POS_TYPE_;
typedef unsigned long   _SES_TYPE_;
typedef unsigned long   _SIZ_TYPE_;
typedef          char * _STR_TYPE_;

typedef enum { _DO_ESCAPE_   = -3,
               _DO_LOAD_     = -2,
               _DO_ACCEPT_   = -1,
               _PICO_DONE_   =  0,
               _AGR_ERROR_   =  1,
               _ATC_ERROR_   =  2,
               _BUF_ERROR_   =  3,
               _CTL_ERROR_   =  4,
               _DCT_ERROR_   =  5,
               _DIG_ERROR_   =  6,
               _DPS_ERROR_   =  7,
               _EXP_ERROR_   =  8,
               _EXT_ERROR_   =  9,
               _IAG_ERROR_   = 10,
               _IDX_ERROR_   = 11,
               _IIX_ERROR_   = 12,
               _ILL_ERROR_   = 13,
               _INF_ERROR_   = 14,
               _IPM_ERROR_   = 15,
               _MEM_ERROR_   = 16,
               _NAB_ERROR_   = 17,
               _NAF_ERROR_   = 18,
               _NAT_ERROR_   = 19,
               _NBR_ERROR_   = 20,
               _NEG_ERROR_   = 21,
               _NMA_ERROR_   = 22,
               _RBC_ERROR_   = 23,
               _RBR_ERROR_   = 24,
               _REE_ERROR_   = 25,
               _REF_ERROR_   = 26,
               _RNG_ERROR_   = 27,
               _RPR_ERROR_   = 28,
               _SIZ_ERROR_   = 29,
               _SNA_ERROR_   = 30,
               _STK_ERROR_   = 31,
               _TAG_ERROR_   = 32,
               _TMS_ERROR_   = 33,
               _TXT_ERROR_   = 34,
               _UDI_ERROR_   = 35,
               _USR_ERROR_   = 36,
               _ZDV_ERROR_   = 37,
               _TQA_ERROR_   = 38,
               _RTH_ERROR_   = 39,
               _RTS_ERROR_   = 40,
               _THR_ERROR_   = 41,
               _TNF_ERROR_   = 42 } _RES_TYPE_;

typedef enum { _ESCAPE_NO_   =  0,
               _ESCAPE_YES_  =  1 } _ESC_TYPE_;

typedef enum { _RECLAIM_NO_  =  0,
               _RECLAIM_YES_ =  1 } _RCL_TYPE_;

/* callback prototypes */

/*------------------------------------------------------------------------*/
/*  _PICO_PRINT_:                                                         */
/*     called when *print* peforms output                                 */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     print string                         */
/*                                                                        */
/*  returns:                                                              */
/*     _ESC_TYPE_             ->     signals request for escape           */
/*------------------------------------------------------------------------*/
_ESC_TYPE_ _PICO_PRINT_(const _SES_TYPE_,
                        const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_ESCAPE_:                                                        */
/*     called by *eval* to check for escape                               */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*                                                                        */
/*  returns:                                                              */
/*     _ESC_TYPE_             ->     signals request for escape           */
/*------------------------------------------------------------------------*/
_ESC_TYPE_ _PICO_ESCAPE_(const _SES_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_DISPLAY_:                                                       */
/*     called by *eval* to display a string                               */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     string to be displayed               */
/*                                                                        */
/*  returns:                                                              */
/*     _ESC_TYPE_             ->     signals request for escape           */
/*------------------------------------------------------------------------*/
_ESC_TYPE_ _PICO_DISPLAY_(const _SES_TYPE_,
                          const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_MARK_:                                                          */
/*     called by *read* to mark a token                                   */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _POS_TYPE_             ->     start position of token              */
/*     _POS_TYPE_             ->     end position of token                */
/*                                                                        */
/*  returns: none                                                         */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _PICO_MARK_(const _SES_TYPE_, 
                       const _POS_TYPE_,
                       const _POS_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_MESSAGE_:                                                       */
/*      called by *read* or *eval* to set optional error message          */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     message string                       */
/*                                                                        */
/*  returns: none                                                         */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _PICO_MESSAGE_(const _SES_TYPE_, 
                          const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_RECLAIM_:                                                       */
/*      called before and after garbage collection                        */
/*                                                                        */
/*  arguments:                                                            */
/*     _RCL_TYPE_             ->     start/stop garbage collection        */
/*                                                                        */
/*  returns: none                                                         */
/*------------------------------------------------------------------------*/
_NIL_TYPE_ _PICO_RECLAIM_(const _RCL_TYPE_);

/* public prototypes */

/*------------------------------------------------------------------------*/
/*  _PICO_INIT_:                                                          */
/*     set up storage for pico                                            */
/*                                                                        */
/*  arguments:                                                            */
/*     _ADR_TYPE_             ->     address of storage                   */
/*     _SIZ_TYPE_             ->     size of storage                      */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_INIT_(const _ADR_TYPE_,
                       const _SIZ_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_SESSION_:                                                       */
/*     activation of pico session                                         */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_SESSION_(const _SES_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_DO_:                                                            */
/*     evaluation of a pico expression                                    */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     input string                         */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_DO_(const _SES_TYPE_,
                     const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_ACCEPT_:                                                        */
/*     continuation of a pico session after accepted user input           */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     input string                         */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_ACCEPT_(const _SES_TYPE_,
                         const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_LOAD_:                                                          */
/*     continuation of a pico session after loaded user input             */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*     _STR_TYPE_             ->     load string                          */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_LOAD_(const _SES_TYPE_,
                       const _STR_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_CONTINUE_:                                                      */
/*     continuation of a pico session after interrupt                     */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_CONTINUE_(const _SES_TYPE_);

/*------------------------------------------------------------------------*/
/*  _PICO_KILL_:                                                          */
/*     deactivation of a pico session                                     */
/*                                                                        */
/*  arguments:                                                            */
/*     _SES_TYPE_             ->     session identity                     */
/*                                                                        */
/*  returns:                                                              */
/*     _RES_TYPE_             ->     result status                        */
/*------------------------------------------------------------------------*/

_RES_TYPE_ _PICO_KILL_(const _SES_TYPE_);
