#ifndef MACSERIALRB_H
#define MACSERIALRB_H 1

#include "ruby.h"
#include "macserial/macserial.h"
#include "macserial/modelinfo.h"

static VALUE models();
static VALUE generate(int argc, VALUE *argv, VALUE self);
static SERIALINFO get_serialinfo(const VALUE model);

#endif /* MACSERIALRB_H */
