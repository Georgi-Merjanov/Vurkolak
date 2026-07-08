#ifndef TYPES_H
#define TYPES_H

#define MAX_NAME 50
#define MAX_ROLE_NAME 20
#define MAX_DESCRIPTION 600
#define MAX_FILENAME 20

extern char filename[MAX_FILENAME];

typedef enum {
    GOOD = 1,  // От добрите (селото)
    BAD,       // От лошите (главатар и вълци)
    SOLO,      // Мазохист
    UNKNOWN    // Още не се знае, защото е Крадец или Двоен Агент
} Team;

typedef enum {
    KRADEC = 1,   // Крадец
    DVOEN_AGENT,  // Двоен агент
    GLAVATAR,     // Главатар
    VULK,         // Вълк
    BEZSUNNICA,   // Безсънница
    GADATEL,      // Гадател
    LEKAR,        // Лекар
    UBIEC,        // Убиец
    MAZOHIST,     // Мазохист
    SELQNIN       // Селянин
} Role_type;

typedef struct {
    Role_type type;                     // Номер на ролята за по-бързо изчисляване
    char name[MAX_ROLE_NAME];           // Име на ролята
    char description[MAX_DESCRIPTION];  // Обяснение на ролята
    Team team;                          // От кой отбор е
} Role;

typedef struct {
    char name[MAX_NAME];  // Името на играча
    Role role;            // Ролята на играча
    Team team;            // Отборът на играча
    int is_alive;         // 1 = жив, 0 = мъртъв
    int is_dvoen_agent;   // 1 = Двоен агент, 0 = не е
    int is_kmet;          // 1 = Кмет (има решаващ глас), 0 = не е
} Player;

#endif