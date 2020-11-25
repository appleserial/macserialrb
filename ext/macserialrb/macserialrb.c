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
#include "macserial/macserial.c"
#include "macserial/modelinfo_autogen.h"

VALUE rb_mMacserialrb;

static VALUE
models()
{
  VALUE obj = rb_ary_new_capa(APPLE_MODEL_MAX);

  for (int32_t idx = 0; idx < APPLE_MODEL_MAX; idx++) {
    rb_ary_push(obj, rb_str_new_cstr(ApplePlatformData[idx].productName));
  }
  return obj;
}

static SERIALINFO
get_serialinfo(VALUE model)
{
  SERIALINFO info = {
    .modelIndex  = -1,
    .decodedYear = -1,
    .decodedWeek = -1,
    .decodedCopy = -1,
    .decodedLine = -1
  };

  // model
  for (int32_t idx = 0; idx < APPLE_MODEL_MAX; idx++) {
    if (strcmp(ApplePlatformData[idx].productName, rb_string_value_cstr(&model)) == 0)
    {
      info.modelIndex = idx;
    }
  }

  return info;
}

static VALUE
generate(int argc, VALUE *argv, VALUE self)
{
  VALUE model = Qnil;
  VALUE obj   = rb_hash_new();

  for (int i = 0; i < argc; ++i)
  {
    model = rb_hash_aref(argv[i], rb_to_symbol( rb_str_new2("model") ));
  }

  if (NIL_P(model))
  {
    rb_raise(rb_eTypeError, "model is required!");
    exit(0);
  }

  SERIALINFO info = get_serialinfo(model);

  if (get_serial(&info)) {
    char mlb[MLB_MAX_SIZE];
    char ssn[MLB_MAX_SIZE];

    get_mlb(&info, mlb, MLB_MAX_SIZE);
    sprintf(ssn, "%s%s%s%s%s", info.country, info.year, info.week, info.line, info.model);

    VALUE productName = rb_str_new2(ApplePlatformData[info.modelIndex].productName);
    VALUE SystemSerialNumber = rb_str_new2(ssn);
    VALUE MLB = rb_str_new2(mlb);

    rb_hash_aset(obj, rb_to_symbol( rb_str_new2("productName") ), productName);
    rb_hash_aset(obj, rb_to_symbol( rb_str_new2("SystemSerialNumber") ), SystemSerialNumber);
    rb_hash_aset(obj, rb_to_symbol( rb_str_new2("MLB") ), MLB);
  }

  return obj;
}

void
Init_macserialrb(void)
{
  rb_mMacserialrb = rb_define_module("Macserialrb");

  rb_define_module_function(rb_mMacserialrb, "models", models, 0);
  rb_define_module_function(rb_mMacserialrb, "generate", generate, -1);
}
