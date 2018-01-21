//
// Created by moritzmg on 20/01/18.
//

#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    cJSON *array_obj1 = cJSON_CreateObject();
    cJSON *array_obj2 = cJSON_CreateObject();
    cJSON *j_array = cJSON_CreateArray();

    cJSON_AddItemToArray(j_array, array_obj1);
    cJSON_AddItemToArray(j_array, array_obj2);

    cJSON_AddStringToObject(array_obj1, "key1", "value1");
    cJSON_AddStringToObject(array_obj1, "key2", "value2");
    cJSON_AddStringToObject(array_obj2, "key1", "value3");
    cJSON_AddStringToObject(array_obj2, "key2", "value4");


    char *str = cJSON_Print(j_array);

    printf("%s\n", str);


    free(str);

    cJSON_Delete(j_array);

    return 0;
}
