#include <YSI_Coding\y_hooks>

#if !defined ITEMTASKS_MIN_ITEMS_PER_TASK
    #define ITEMTASKS_MIN_ITEMS_PER_TASK     (1)
#endif

#if !defined ITEMTASKS_MAX_ITEMS_PER_TASK
    #define ITEMTASKS_MAX_ITEMS_PER_TASK     (5)
#endif

forward ItemTasks_SetPlayerRandomTask(playerid);
forward ItemTasks_SetPlayerTask(playerid, const ItemType:items[], size = sizeof items);
forward ItemTasks_CompletePlayerTask(playerid);
forward bool:ItemTasks_HasPlayerActiveTask(playerid);
forward OnPlayerCompleteTask(playerid, totalReward);

static ItemType:s_playerTaskItems[MAX_PLAYERS][ITEMTASKS_MAX_ITEMS_PER_TASK] = { INVALID_ITEM_TYPE, ... };

hook OnPlayerDisconnected(playerid) {
    for (new i; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        s_playerTaskItems[playerid][i] = INVALID_ITEM_TYPE;
    }
}

stock ItemTasks_SetPlayerTask(playerid, const ItemType:items[]) {
    if (ItemTasks_HasPlayerActiveTask(playerid)) {
        return 0;
    }

    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(items[i])) {
            continue;
        }

        s_playerTaskItems[playerid][i] = items[i];
    }

    return 1;
}

stock ItemTasks_SetPlayerRandomTask(playerid) {
    new totalTaskItems,
    itemsToBring,
    ItemType:item;

    if (ItemTasks_HasPlayerActiveTask(playerid)) {
        return 0;
    }

    totalTaskItems = ItemTasks_GetTotalDefinedItems();
    itemsToBring = Random(ITEMTASKS_MIN_ITEMS_PER_TASK, ITEMTASKS_MAX_ITEMS_PER_TASK);

    for (new i = 0; i < itemsToBring; i++) {
        item = ItemTasks_GetItemTypeByIndex(Random(0, totalTaskItems));
        s_playerTaskItems[playerid][i] = item;
    }

    return 1;
}

stock ItemTasks_CompletePlayerTask(playerid) {
    if (!ItemTasks_HasPlayerActiveTask(playerid)) {
        return 0;
    }

    new totalReward;

    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(s_playerTaskItems[playerid][i])) {
            break;
        }

        new ItemType:item = s_playerTaskItems[playerid][i];
        totalReward += ItemTasks_GetItemTypeReward(item);
    }

    CallLocalFunction("OnPlayerCompleteTask", "dd", playerid, totalReward);
    
    for (new i = 0; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        s_playerTaskItems[playerid][i] = INVALID_ITEM_TYPE;
    }

    return 1;
}

stock ItemTasks_GetPlayerTaskItems(playerid, ItemType:items[ITEMTASKS_MAX_ITEMS_PER_TASK] = { INVALID_ITEM_TYPE, ... }) {
    if (!ItemTasks_HasPlayerActiveTask(playerid)) {
        return 0;
    }

    new count;

    for (new i; i < ITEMTASKS_MAX_ITEMS_PER_TASK; i++) {
        if (!ItemTasks_IsItemTypeDefined(s_playerTaskItems[playerid][i])) {
            continue;
        }

        items[i] = s_playerTaskItems[playerid][i];
        count++;
    }

    return count;
}

stock bool:ItemTasks_HasPlayerActiveTask(playerid) {
    if(s_playerTaskItems[playerid][0] == INVALID_ITEM_TYPE) {
        return false;
    }

    return true;
}
