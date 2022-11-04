// generated by "sampctl package init"
#include <a_samp>
#include <itemtasks>

main() {}

public OnGameModeInit() {
    new ItemType:item_Marijuana = DefineItemType("Marijuana", "Marijuana", 3027, 1, 0.0);
    new ItemType:item_Toolbox = DefineItemType("Toolbox", "Toolbox", 19921, 1, 0.0);
    new ItemType:item_Tire = DefineItemType("Tire", "Tire", 1098, 1, 0.0);


    ItemTasks_DefineItemType(item_Marijuana, 20);
    ItemTasks_DefineItemType(item_Toolbox, 5);
    ItemTasks_DefineItemType(item_Tire, 2);

    Player_SetItemTask(0);
    printf("----------------------------------------");
    Player_SetItemTask(1);
    printf("----------------------------------------");
    Player_SetItemTask(2);

    new ItemType:arr[ITEMTASKS_MAX_ITEMS_PER_TASK];

    Player_GetActiveTaskItemTypes(1, arr);

    for (new i = 0; i < sizeof(arr); i++) {
        printf("Item: %d", _:arr[i]);
    }

    Player_CompleteTask(1);
}
