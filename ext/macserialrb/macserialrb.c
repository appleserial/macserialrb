#include "macserialrb.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#endif

#include "macserial/macserial.h"
#include "macserial/modelinfo.h"
#include "macserial/modelinfo_autogen.h"

VALUE rb_mMacserialrb;

static VALUE
models(VALUE self)
{
  VALUE arr = rb_ary_new_capa(APPLE_MODEL_MAX);

  for (int32_t idx = 0; idx < APPLE_MODEL_MAX; idx++) {
    rb_ary_push(arr, rb_str_new_cstr(ApplePlatformData[idx].productName));
  }
  return arr;
}

void
Init_macserialrb(void)
{
  rb_mMacserialrb = rb_define_module("Macserialrb");

  rb_define_module_function(rb_mMacserialrb, "models", models, 0);
}

// Tuning options:
//  --model <model>  (-m)  mac model used for generation
//  --num <num>      (-n)  number of generated pairs
//  --year <year>    (-y)  year used for generation
//  --week <week>    (-w)  week used for generation
//  --country <loc>  (-c)  country location used for generation
//  --copy <copy>    (-o)  production copy index
//  --line <line>    (-e)  production line
//  --platform <ppp> (-p)  platform code used for generation
