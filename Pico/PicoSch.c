#include "Pico.h"
#include "PicoMai.h"
#include "PicoMem.h"
#include "PicoEnv.h"
#include "PicoNat.h"

/* private variables */

_UNS_TYPE_ _SCH_CTR_;

/* public variables */

_EXP_TYPE_ _SCH_;
_EXP_TYPE_ _SCH_CURRENT_;

_NIL_TYPE_ _scheduler_initialize_(_NIL_TYPE_)
 { _SCH_CTR_ = 1;
   _SCH_ = _VOID_;
   _SCH_CURRENT_ = _VOID_; }
    
_EXP_TYPE_ _scheduler_add_(_EXP_TYPE_ thr, _EXP_TYPE_ tid)
 { _EXP_TYPE_ ctr, sch;
   _mem_claim_();
   sch = _ag_make_SCH_();
   ctr = _ag_make_NBU_(_SCH_CTR_);
   _ag_set_TID_TID_(tid, ctr);
   _ag_set_THR_TID_(thr, ctr);
   _ag_set_SCH_THR_(sch, thr);
   _ag_set_SCH_SCH_(sch, _SCH_);
   _SCH_CTR_++;
   _SCH_ = sch;
   if(_ag_is_VOI_(_SCH_CURRENT_))
     _SCH_CURRENT_ = _SCH_;
   return sch; }

_EXP_TYPE_ _scheduler_find_(_EXP_TYPE_ tid)
 { _EXP_TYPE_ src, thr;
   src = _SCH_;
   while(!_ag_is_VOI_(src))
     { thr = _ag_get_SCH_THR_(src);
       if(_mem_is_same_(_ag_get_THR_TID_(thr),
                        _ag_get_TID_TID_(tid)))
         return src;
       src = _ag_get_SCH_SCH_(src); }
   _error_(_TNF_ERROR_); }

_EXP_TYPE_ _scheduler_next_(_NIL_TYPE_)
 { _EXP_TYPE_ nxt;
   nxt = _ag_get_SCH_SCH_(_SCH_CURRENT_);
   if(_ag_is_VOI_(nxt))
     nxt = _SCH_;
   return nxt; }
