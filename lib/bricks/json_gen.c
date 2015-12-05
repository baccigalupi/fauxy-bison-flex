#include "json_gen.h"

FxB_String *fxb_json_gen_bald_pair(FxB_String *key, FxB_String *value) {
  FxB_String *pair = NULL;
  verify(key);
  verify(value);

  if (fxb_string_value(key)[0] != '"') {
    fxb_string_wrap(key, '"', '"');
  }

  pair = FxB_String_create(fxb_string_value(key));
  verify(pair);
  verify(fxb_string_add_chars(pair, ": "));
  verify(fxb_string_add_string(pair, value));

  return pair;
error:
  if (pair) { fxb_string_free(pair); }
  return NULL;
}

FxB_String *fxb_json_gen_join_pairs(FxB_Array *pairs, char *joiner) {
  FxB_String *joined = FxB_String_create_blank();
  verify(joined);

  int length = fxb_array_length(pairs);
  int i;
  for(i = 0; i < length; i++) {
    verify(fxb_string_add_string(joined, fxb_array_get(pairs, i)));
    if (i < length - 1) {
      verify(fxb_string_add_chars(joined, joiner));
    }
  }

  return joined;
error:
  if (joined) { fxb_string_free(joined); }
  return NULL;
}

FxB_String *fxb_json_gen_wrap_pairs(FxB_Array *pairs) {
  FxB_String *json = fxb_json_gen_join_pairs(pairs, ", ");
  verify(json);

  verify(fxb_string_wrap(json, '{', '}'));
  return json;
error:
  if (json) { fxb_string_free(json); }
  return NULL;
}

FxB_String *fxb_json_gen_wrap_array_pairs(FxB_Array *pairs) {
  FxB_String *json = fxb_json_gen_join_pairs(pairs, ",\n");
  verify(json);
  verify(fxb_string_wrap(json, '\n', '\n'));
  verify(fxb_string_wrap(json, '[', ']'));
  return json;
error:
  if (json) { fxb_string_free(json); }
  return NULL;
}
