#include "../../../lib/parser/tokens.h"
#include "../../../lib/interpreter/pool.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/native/boolean_methods.h"
#include "../../../lib/native/object_methods.h"
#include "../../../lib/native/nil_methods.h"
#include "../lib/spec.h"

// TODO: swap this out for interpreter helpers
#define create_config() FxB_HashMap_create(1)

FxI_Pool *setup_test_literal_pool() {
  FxB_HashMap *config = create_config();
  FxI_Pool *pool = FxI_Pool_create(config);

  FxP_Expression *false_literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  FxN_Object *false_object = FxN_Boolean_create(pool, false_literal);

  FxP_Expression *true_literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *true_object = FxN_Boolean_create(pool, true_literal);

  FxP_Expression *nil_literal = FxP_Literal_create(NULL, TOKEN_NIL);
  FxN_Object *nil_object = FxN_Nil_create(pool, nil_literal);

  fxi_literal_set(pool, FALSE_KEY, false_object);
  fxi_literal_set(pool, TRUE_KEY, true_object);
  fxi_literal_set(pool, NIL_KEY, nil_object);

  return pool;
}

char *test_object_without_attributes_emptines() {
  spec_describe("empty on objects without attributes");

  FxI_Pool *pool = setup_test_literal_pool();
  FxN_Object *false_object = fxi_literal_get(pool, FALSE_KEY);

  FxN_Object *object = FxN_Object_create(pool, NULL);

  assert_equal(false_object, fxn_object_is_empty(object), "is false");

  return NULL;
}

char *test_object_with_attributes_emptines() {
  spec_describe("non-empty object truthiness");

  FxI_Pool *pool = setup_test_literal_pool();
  FxN_Object *true_object = fxi_literal_get(pool, TRUE_KEY);

  FxN_Object *object = FxN_Object_create(pool, NULL);
  fxn_object_set_attribute(object, "flag", true_object);

  assert_equal(true_object, fxn_object_is_empty(object), "is true");

  return NULL;
}

char *test_object_nilness() {
  spec_describe("nilness of objects");

  FxI_Pool *pool = setup_test_literal_pool();
  FxN_Object *nil_object =  fxi_literal_get(pool, NIL_KEY);
  FxN_Object *true_object = fxi_literal_get(pool, TRUE_KEY);

  assert_equal(fxn_object_is_nil(nil_object), true_object, "nil object is in the pool");

  return NULL;
}

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  run_spec(test_object_without_attributes_emptines);
  run_spec(test_object_with_attributes_emptines);
  run_spec(test_object_nilness);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
