#include <YSI_Coding\y_hooks>

#if !defined ITEMTASKS_MIN_ITEMS_PER_TASK
    #define ITEMTASKS_MIN_ITEMS_PER_TASK     (1)
#endif

#if !defined ITEMTASKS_MAX_ITEMS_PER_TASK
    #define ITEMTASKS_MAX_ITEMS_PER_TASK     (5)
#endif

forward Player_SetRandomTask(playerid);
forward Player_SetTask(playerid, const ItemType:items[], size = sizeof items);
forward Player_CompleteTask(playerid);
forward bool:Player_HasActiveTask(playerid);
forward OnPlayerCompleteTask(playerid, totalReward);

static ItemType:playerTaskItems[MAX_PLAYERS][ITEMTASKS_MAX_ITEMS_PER_TASK] = { INVALID_ITEM_TYPE, ... };

hook OnPlayerDisconnected(playerid) {
    for (new i; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        playerTaskItems[playerid][i] = INVALID_ITEM_TYPE;
    }
}

stock Player_SetTask(playerid, const ItemType:items[]) {
    if (Player_HasActiveTask(playerid)) {
        return 0;
    }

    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(items[i])) {
            continue;
        }

        playerTaskItems[playerid][i] = items[i];
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

    totalTaskItems = ItemTasks_GetTotalDefinedItems();
    itemsToBring = Random(ITEMTASKS_MIN_ITEMS_PER_TASK, ITEMTASKS_MAX_ITEMS_PER_TASK);

    for (new i = 0; i < itemsToBring; i++) {
        item = ItemTasks_GetItemTypeByIndex(Random(0, totalTaskItems));
        playerTaskItems[playerid][i] = item;
    }

    return 1;
}

stock Player_CompleteTask(playerid) {
    if (!Player_HasActiveTask(playerid)) {
        return 0;
    }

    new totalReward;

    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(playerTaskItems[playerid][i])) {
            break;
        }

        new ItemType:item = playerTaskItems[playerid][i];
        totalReward += ItemTasks_GetItemTypeReward(item);
    }

    CallLocalFunction("OnPlayerCompleteTask", "dd", playerid, totalReward);
    
    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        playerTaskItems[playerid][i] = INVALID_ITEM_TYPE;
    }

    return 1;
}

stock Player_GetActiveTaskItemTypes(playerid, ItemType:items[ITEMTASKS_MAX_ITEMS_PER_TASK] = { INVALID_ITEM_TYPE, ... }) {
    if (!Player_HasActiveTask(playerid)) {
        return 0;
    }

    new count;

    for (new i; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(playerTaskItems[playerid][i])) {
            continue;
        }

        items[i] = playerTaskItems[playerid][i];
        count++;
    }

    return count;
}

stock bool:Player_HasActiveTask(playerid) {
    if(playerTaskItems[playerid][0] == INVALID_ITEM_TYPE) {
        return false;
    }

    return true;
}
