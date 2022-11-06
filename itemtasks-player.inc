#include <YSI_Coding\y_hooks>

#if !defined ITEMTASKS_MIN_ITEMS_PER_TASK
    #define ITEMTASKS_MIN_ITEMS_PER_TASK     (0)
#endif

#if !defined ITEMTASKS_MAX_ITEMS_PER_TASK
    #define ITEMTASKS_MAX_ITEMS_PER_TASK     (5)
#endif

forward Player_SetRandomTask(playerid);
forward Player_SetTask(playerid, const ItemType:items[], size = sizeof items);
forward Player_CompleteTask(playerid);
forward bool:Player_HasActiveTask(playerid);
forward OnPlayerCompleteTask(playerid, totalReward);

static List:playerTaskItems[MAX_PLAYERS] = { INVALID_LIST, ... };

hook OnPlayerDisconnected(playerid) {
    if (list_valid(playerTaskItems[playerid])) {
        list_delete(playerTaskItems[playerid]);
    }
}

stock Player_SetTask(playerid, const ItemType:items[], size = sizeof items) {
    new List:list = playerTaskItems[playerid];

    if (Player_HasActiveTask(playerid)) {
        return 0;
    }

    if (!list_valid(list)) {
        list = list_new();
    }

    for (new i = 0; i < size; i++) {
        if (!ItemTasks_IsItemTypeDefined(items[i])) {
            continue;
        }

        list_add(list, _:items[i]);
    }

    return 1;
}

stock Player_SetRandomTask(playerid) {
    new totalTaskItems,
    itemsToBring,
    ItemType:item;

    if (Player_HasActiveTask(playerid)) {
        return 0;
    }

    if (!list_valid(playerTaskItems[playerid])) {
        playerTaskItems[playerid] = list_new();
    }

    totalTaskItems = ItemTasks_GetTotalDefinedItems();
    itemsToBring = Random(ITEMTASKS_MIN_ITEMS_PER_TASK, ITEMTASKS_MAX_ITEMS_PER_TASK);

    for (new i = 0; i < itemsToBring; i++) {
        item = ItemTasks_GetItemTypeByIndex(Random(0, totalTaskItems - 1));

        if (!IsValidItemType(item)) {
            continue;
        }

        list_add(playerTaskItems[playerid], _:item);
    }

    return 1;
}

stock Player_CompleteTask(playerid) {
    if (!list_valid(playerTaskItems[playerid])) {
        return 0;
    }

    new totalReward;

    for (new i = 0; i < list_size(playerTaskItems[playerid]); i++) {
        new ItemType:item = ItemType:list_get(playerTaskItems[playerid], i);
        totalReward += ItemTasks_GetItemTypeReward(item);
    }

    CallLocalFunction("OnPlayerCompleteTask", "dd", playerid, totalReward);

    list_delete(playerTaskItems[playerid]);

    return 1;
}

stock Player_GetActiveTaskItemTypes(playerid, ItemType:items[], size = sizeof(items)) {
    if (!list_valid(playerTaskItems[playerid])) {
        return 0;
    }

    if (size < list_size(playerTaskItems[playerid])) {
        printf("Player_GetActiveTaskItemTypes: size is too small. Use ITEMTASKS_MAX_ITEMS_PER_TASK as max size.");
        return -1;
    }

    for (new i; i < size; i++) {
        items[i] = ItemType:list_get(playerTaskItems[playerid], i);
    }

    return 1;
}

stock bool:Player_HasActiveTask(playerid) {
    if (!list_valid(playerTaskItems[playerid])) {
        return false;
    }

    if (list_size(playerTaskItems[playerid]) == 0) {
        return false;
    }

    return true;
}
