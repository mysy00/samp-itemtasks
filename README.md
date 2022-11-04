# samp-itemtasks

[![sampctl](https://img.shields.io/badge/sampctl-samp--itemtasks-2f2f2f.svg?style=for-the-badge)](https://github.com/mysy00/samp-itemtasks)

API for simple tasks using Southclaw's item system.
We use it on our server for simple quests where you have to find and bring a few items to get a reward.

## Installation

Simply install to your project:

```bash
sampctl package install mysy00/samp-itemtasks
```

Include in your code and begin using the library:

```pawn
#include <itemtasks>
```

## Usage

```pawn
forward ItemTasks_DefineItemType(ItemType:itemtype, reward);
forward ItemType:ItemTasks_GetItemTypeByIndex(index);
forward ItemTasks_GetTotalDefinedItems();
forward ItemTasks_GetItemTypeReward(ItemType:itemtype);

forward Player_SetItemTask(playerid);
forward Player_CompleteTask(playerid);
forward bool:Player_HasActiveTask(playerid);
forward OnPlayerCompleteTask(playerid, totalReward);
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
