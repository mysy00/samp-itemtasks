#include <item>
#include <PawnPlus>
#include <YSI_Coding\y_hooks>

forward ItemTasks_DefineItemType(ItemType:itemtype, reward);
forward ItemType:ItemTasks_GetItemTypeByIndex(index);
forward ItemTasks_GetTotalDefinedItems();
forward ItemTasks_GetItemTypeReward(ItemType:itemtype);
forward bool:ItemTasks_IsItemTypeDefined(ItemType:itemtype);

static
Map:definedItems,
List:itemsInTasks;
// An extra list, so we can easily select a random item from the list.
// There seem to be no way(?) to select a random value from a map that
// will be as performant as a helper list.


hook OnGameModeInit() {
    definedItems = map_new();
    itemsInTasks = list_new();
}

ItemTasks_DefineItemType(ItemType:itemtype, reward) {
    if (!IsValidItemType(itemtype)) {
        return 0;
    }

    map_add(definedItems, _:itemtype, reward);
    list_add(itemsInTasks, _:itemtype);

    return 1;
}

stock ItemType:ItemTasks_GetItemTypeByIndex(index) {
    if (!list_valid(itemsInTasks)) {
        return INVALID_ITEM_TYPE;
    }

    new
    value,
    ret;

    ret = list_get_safe(itemsInTasks, index, value);

    if (!ret) {
        return INVALID_ITEM_TYPE;
    }

    if (!IsValidItemType(ItemType:value)) {
        return INVALID_ITEM_TYPE;
    }

    return ItemType:value;
}

stock ItemTasks_GetTotalDefinedItems() {
    if (!list_valid(itemsInTasks)) {
        return 0;
    }

    return list_size(itemsInTasks);
}

stock ItemTasks_GetItemTypeReward(ItemType:itemtype) {
    if (!IsValidItemType(itemtype)) {
        return 0;
    }

    if (!map_valid(definedItems)) {
        return 0;
    }

    return map_get(definedItems, _:itemtype);
}

stock bool:ItemTasks_IsItemTypeDefined(ItemType:itemtype) {
    if (!IsValidItemType(itemtype)) {
        return false;
    }

    return map_has_key(definedItems, _:itemtype);
}

#include "itemtasks-player"