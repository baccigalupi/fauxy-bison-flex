#ifndef FxN_Object_h
#define FxN_Object_h 1

#include "../bricks/hash_map.h"
#include "class.h"

typedef struct FxN_Object {
  FxN_Class   *scope;
  FxB_HashMap *attributes;
} FxN_Object;

#define fxn_object_scope(O)                 ((O)->scope)
#define fxn_object_attributes(O)            ((O)->attributes)
#define fxn_object_mapped_attr_get(O, K)    (hash_map_get(fxn_object_attributes(O), K))
#define fxn_object_mapped_attr_set(O, K, V) (hash_map_set(fxn_object_attributes(O), K, V))

#define fxn_object_free(O)                  (fxn_class_free(fxn_object_scope(O)), hash_map_free(fxn_object_attributes(O)), fx_pfree(O))


FxN_Object *FxN_Object_create(FxN_Class *scope);
FxN_Object *fxn_object_get_attribute(FxN_Object *self, FxB_String *key);
void        fxn_object_set_attribute(FxN_Object *self, FxB_String *key, FxN_Object *value);

#endif