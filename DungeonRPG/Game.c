#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "Player.h"

#define SKIPHEADER 3

char message[200];

void openFile(int roomToOpen);

/*fread(void *ptr, size_t size,
size_t count, FILE *stream);*/

struct Room {
    int currentNum;
    char currentTitle[100];
    char currentItemsRequired[100];
    char currentDescription[600];
    char currentItemsContained[200];
    char currentExits[100];
};

struct Room newRoom;

void openFile(int roomToOpen) {
    char roomOpen[256];
    sprintf(roomOpen, "/Users/nikhilthankasala/Desktop/ECE13/nthankas/Lab08/Lab08/Lab08/RoomFiles/room%d.txt", roomToOpen);
    FILE *currentFile;
    currentFile = fopen(roomOpen, "rb");
    
    newRoom.currentNum = roomToOpen;
    
    int currentIndex = SKIPHEADER;
    fseek(currentFile, currentIndex, SEEK_SET);
    unsigned long titleLength = 0;
    fread(&titleLength, 1, 1, currentFile);
    char title[100] = "";
    unsigned long ret = fread((void *)title, 1, titleLength, currentFile);
    
    title[ret] = '\0';
    
    strcpy(newRoom.currentTitle, title);
    
//    printf("Room Number: %d\n", roomToOpen);
    printf("Room Title: %s\n", title);
    
    currentIndex += titleLength + 1;
    fseek(currentFile, currentIndex, SEEK_SET);
    
    unsigned long itemReqLen = 0;
    fread(&itemReqLen, 1, 1, currentFile);
    char items[100] = "";
    unsigned long ret2 = fread((void *)items, 1, itemReqLen, currentFile);
    
    items[ret2] = '\0';
//    printf("Item # required: %ld\n", itemReqLen);
//    char itemString[100] = "Items required:";
//    for (int i = 0; i <= itemReqLen; i++) {
//        if ((int)items[i] == '\x01') {
//            char darkKey[20] = " Dark Key";
//            strncat(itemString, darkKey, 20);
//        }
//        else if ((int)items[i] == '\x02') {
//            char jailKey[20] = " Jail Key";
//            strncat(itemString, jailKey, 20);
//        }
//        else if ((int)items[i] == '\x03') {
//            char castleKey[20] = " Castle Key";
//            strncat(itemString, castleKey, 10);
//        }
//        else if (((int)items[i] == '\0') && (i == 0)) {
//            char none[20] = " None";
//            strncat(itemString, none, 20);
//        }
//    }
    for (int i = 0; i <= itemReqLen; i++) {
        newRoom.currentItemsRequired[i] = items[i];
    }
    currentIndex += itemReqLen + 1;
    fseek(currentFile, currentIndex, SEEK_SET);
    
    unsigned long descriptionLen = 0;
    unsigned long itemsContainedLen = 0;
    
    char description[600] = "";
    char itemsContained[100] = "";
    char exits[100] = "";
    int skip = 1;
    if (itemReqLen > 0) {
        for (int i = 0; i < itemReqLen; i++) {
            
            long num = items[i];
            if (FindInInventory(num)) {
                skip = 0;
            }
            else {
                skip = 1;
            }
        }
    }
    
    if ((skip == 1) && (itemReqLen > 0)){
        fread(&descriptionLen, 1, 1, currentFile);
        currentIndex += descriptionLen + 1;
        fseek(currentFile, currentIndex, SEEK_SET);
        fread(&itemsContainedLen, 1, 1, currentFile);
        currentIndex += itemsContainedLen + 1;
        currentIndex += 4; //to skip exits for first room version
        fread(&itemReqLen, 1, 1, currentFile);
        currentIndex += 1; //skip items required, since for the second version, there cannot be items required
        fseek(currentFile, currentIndex, SEEK_SET);
        fread(&descriptionLen, 1, 1, currentFile);
        unsigned long ret4 = fread((void *)description, 1, descriptionLen, currentFile);
        
        description[ret4] = '\0';
        
        strcpy(newRoom.currentDescription, description);
        
        printf("%s\n", description);
        
        currentIndex += descriptionLen + 1;
        fseek(currentFile, currentIndex, SEEK_SET);
        
        fread(&itemsContainedLen, 1, 1, currentFile);
        unsigned long ret5 = fread((void *)itemsContained, 1, itemsContainedLen, currentFile);
        
        itemsContained[ret5] = '\0';
        for (int i = 0; i <= itemsContainedLen; i++) {
            newRoom.currentItemsContained[i] = itemsContained[i];
        }
        
//        printf("This room contains:\n");
        
        for (int i = 0; i <= itemsContainedLen; i++) {
            if ((int)itemsContained[i] == '\x01') {
//                printf("Dark Key\n");
                AddToInventory(itemsContained[i]);
            }
            else if ((int)itemsContained[i] == '\x02') {
//                printf("Jail Key\n");
                AddToInventory(itemsContained[i]);
            }
            else if ((int)itemsContained[i] == '\x03') {
//                printf("Castle Key\n");
                AddToInventory(itemsContained[i]);
            }
            else if (((int)itemsContained[i] == '\0') && (i == 0)) {
//                printf("Nothing\n");
            }

        }
        
        currentIndex += itemsContainedLen + 1;
        fseek(currentFile, currentIndex, SEEK_SET);
        
        unsigned long ret6 = fread((void *)exits, 1, 4, currentFile);
        
        exits[ret6] = '\0';
        for (int i = 0; i <= 3; i++) {
            newRoom.currentExits[i] = exits[i];
        }
        printf("Possible Exits:\n");
        
        if (exits[0] != '\0') {
            printf(" North Exit exists. \n");
        }
        
        if (exits[1] != '\0') {
            printf(" East Exit exists. \n");
        }
        
        if (exits[2] != '\0') {
            printf(" South Exit exists. \n");
        }
        
        if (exits[3] != '\0') {
            printf(" West Exit exists. \n");
        }
        
        
    }
    else {
        fread(&descriptionLen, 1, 1, currentFile);
        unsigned long ret7 = fread((void *)description, 1, descriptionLen, currentFile);
        description[ret7] = '\0';
        strcpy(newRoom.currentDescription, description);
        printf("%s\n", description);
        
        currentIndex += descriptionLen + 1;
        fseek(currentFile, currentIndex, SEEK_SET);
        
        fread(&itemsContainedLen, 1, 1, currentFile);
        unsigned long ret8 = fread((void *)itemsContained, 1, itemsContainedLen, currentFile);
        
        
        itemsContained[ret8] = '\0';
        for (int i = 0; i <= itemsContainedLen; i++) {
            newRoom.currentItemsContained[i] = itemsContained[i];
        }
        
        //        printf("This room contains:\n");
                
                for (int i = 0; i <= itemsContainedLen; i++) {
                    if ((int)itemsContained[i] == '\x01') {
        //                printf("Dark Key\n");
                        AddToInventory(itemsContained[i]);
                    }
                    else if ((int)itemsContained[i] == '\x02') {
        //                printf("Jail Key\n");
                        AddToInventory(itemsContained[i]);
                    }
                    else if ((int)itemsContained[i] == '\x03') {
        //                printf("Castle Key\n");
                        AddToInventory(itemsContained[i]);
                    }
                    else if (((int)itemsContained[i] == '\0') && (i == 0)) {
        //                printf("Nothing\n");
                    }

                }

        
        currentIndex += itemsContainedLen + 1;
        fseek(currentFile, currentIndex, SEEK_SET);
        
        unsigned long ret9 = fread((void *)exits, 1, 4, currentFile);
        
        exits[ret9] = '\0';
        for (int i = 0; i <= 3; i++) {
            newRoom.currentExits[i] = exits[i];
        }
        printf("Possible Exits:\n");
        
        if (exits[0] != '\0') {
            printf(" North Exit exists. \n");
        }
        
        if (exits[1] != '\0') {
            printf(" East Exit exists. \n");
        }
        
        if (exits[2] != '\0') {
            printf(" South Exit exists. \n");
        }
        
        if (exits[3] != '\0') {
            printf(" West Exit exists. \n");
        }
        
        printf("\n");
        
    }
}

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void) {
    if ((GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) == GAME_ROOM_EXIT_NORTH_EXISTS) {
        newRoom.currentNum = newRoom.currentExits[0];
        openFile(newRoom.currentNum);
        return SUCCESS;
    }
    else {
        return STANDARD_ERROR;
    }
}

/**
 * @see GameGoNorth
 */
    int GameGoEast(void) {
        if ((GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) == GAME_ROOM_EXIT_EAST_EXISTS) {
            newRoom.currentNum = newRoom.currentExits[1];
            openFile(newRoom.currentNum);
            return SUCCESS;
        }
        else {
            return STANDARD_ERROR;
        }
    }
    
/**
 * @see GameGoNorth
 */
    int GameGoSouth(void) {
        if ((GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) == GAME_ROOM_EXIT_SOUTH_EXISTS) {
            newRoom.currentNum = newRoom.currentExits[2];
            openFile(newRoom.currentNum);
            return SUCCESS;
        }
        else {
            return STANDARD_ERROR;
        }
    }

/**
 * @see GameGoNorth
 */
    int GameGoWest(void) {
        if ((GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) == GAME_ROOM_EXIT_WEST_EXISTS) {
            newRoom.currentNum = newRoom.currentExits[3];
            openFile(newRoom.currentNum);
            return SUCCESS;
        }
        else {
            return STANDARD_ERROR;
        }
    }

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
    int GameInit(void) {
        openFile(STARTING_ROOM);
        if (newRoom.currentNum == STARTING_ROOM) {
            return SUCCESS;
        }
        else {
            return STANDARD_ERROR;
        }
        
    }

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title) {
    title = newRoom.currentTitle;
    return (int)strlen(title) + 1;
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc) {
    desc = newRoom.currentDescription;
    return (int)strlen(desc) + 1;
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
    uint8_t GameGetCurrentRoomExits(void) {
        uint8_t roomExits = 0;
        if (newRoom.currentExits[0] != '\0') {
            roomExits = roomExits | GAME_ROOM_EXIT_NORTH_EXISTS;
        }
        
        if (newRoom.currentExits[1] != '\0') {
            roomExits = roomExits | GAME_ROOM_EXIT_EAST_EXISTS;
        }
        
        if (newRoom.currentExits[2] != '\0') {
            roomExits = roomExits | GAME_ROOM_EXIT_SOUTH_EXISTS;
        }
        
        if (newRoom.currentExits[3] != '\0') {
            roomExits = roomExits | GAME_ROOM_EXIT_WEST_EXISTS;
        }
        
        return roomExits;
    }
