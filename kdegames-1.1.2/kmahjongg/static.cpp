/*
*  Note: 
*  Each tile is represented by four characters '1', '2', '3', '4'
*  Array consists of 5 levels each with 32x16 pieces.
*  Number of tiles must be even.
*  Tiles may not float
*/

char ClassicMask[] = {
    // Level 0 -------------------------
    "...121212121212121212121212....."
    "...434343434343434343434343....."
    ".......1212121212121212........."
    ".......4343434343434343........."
    ".....12121212121212121212......."
    ".....43434343434343434343......."
    "...121212121212121212121212....."
    ".124343434343434343434343431212."
    ".431212121212121212121212124343."
    "...434343434343434343434343....."
    ".....12121212121212121212......."
    ".....43434343434343434343......."
    ".......1212121212121212........."
    ".......4343434343434343........."
    "...121212121212121212121212....."
    "...434343434343434343434343....."
    // Level 1 -------------------------
    "................................"
    "................................"
    ".........121212121212..........."
    ".........434343434343..........."
    ".........121212121212..........."
    ".........434343434343..........."
    ".........121212121212..........."
    ".........434343434343..........."
    ".........121212121212..........."
    ".........434343434343..........."
    ".........121212121212..........."
    ".........434343434343..........."
    ".........121212121212..........."
    ".........434343434343..........."
    "................................"
    "................................"
    // Level 2 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "...........12121212............."
    "...........43434343............."
    "...........12121212............."
    "...........43434343............."
    "...........12121212............."
    "...........43434343............."
    "...........12121212............."
    "...........43434343............."
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 3 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    ".............1212..............."
    ".............4343..............."
    ".............1212..............."
    ".............4343..............."
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 4 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "..............12................"
    "..............43................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
};


char TowerMask[] = {
    // Level 0 -------------------------
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    // Level 1 -------------------------
    "................................"
    "................................"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "................................"
    "................................"
    // Level 2 -------------------------
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
    // Level 3 -------------------------
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
    // Level 4 -------------------------
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
    "................................"
    "................................"
    "......121212........121212......"
    "......434343........434343......"
    "......121212........121212......"
    "......434343........434343......"
    "................................"
    "................................"
};


char PyramideMask[] = {
    // Level 0 -------------------------
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    "....121212121212121212121212...."
    "....434343434343434343434343...."
    // Level 1 -------------------------
    "................................"
    "................................"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "......12121212121212121212......"
    "......43434343434343434343......"
    "................................"
    "................................"
    // Level 2 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "........1212121212121212........"
    "........4343434343434343........"
    "........1212121212121212........"
    "........4343434343434343........"
    "........1212121212121212........"
    "........4343434343434343........"
    "........1212121212121212........"
    "........4343434343434343........"
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 3 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "..........121212121212.........."
    "..........434343434343.........."
    "..........121212121212.........."
    "..........434343434343.........."
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 4 -------------------------
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "............12121212............"
    "............43434343............"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
};


char TriangleMask[] = {
    // Level 0 -------------------------
    ".121212121212121212121212121212."
    ".434343434343434343434343434343."
    "...12121212121212121212121212..."
    "...43434343434343434343434343..."
    ".....1212121212121212121212....."
    ".....4343434343434343434343....."
    ".......121212121212121212......."
    ".......434343434343434343......."
    ".........12121212121212........."
    ".........43434343434343........."
    "...........1212121212..........."
    "...........4343434343..........."
    ".............121212............."
    ".............434343............."
    "...............12..............."
    "...............43..............."
    // Level 1 -------------------------
    "...12121212121212121212121212..."
    "...43434343434343434343434343..."
    ".....1212121212121212121212....."
    ".....4343434343434343434343....."
    ".......121212121212121212......."
    ".......434343434343434343......."
    ".........12121212121212........."
    ".........43434343434343........."
    "...........1212121212..........."
    "...........4343434343..........."
    ".............121212............."
    ".............434343............."
    "...............12..............."
    "...............43..............."
    "................................"
    "................................"
    // Level 2 -------------------------
    ".....1212121212121212121212....."
    ".....4343434343434343434343....."
    ".......121212121212121212......."
    ".......434343434343434343......."
    ".........12121212121212........."
    ".........43434343434343........."
    "...........1212121212..........."
    "...........4343434343..........."
    ".............121212............."
    ".............434343............."
    "...............12..............."
    "...............43..............."
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 3 -------------------------
    ".......121212121212121212......."
    ".......434343434343434343......."
    ".........12121212121212........."
    ".........43434343434343........."
    "...........1212121212..........."
    "...........4343434343..........."
    ".............121212............."
    ".............434343............."
    "...............12..............."
    "...............43..............."
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    // Level 4 -------------------------
    ".........12121212121212........."
    ".........43434343434343........."
    "...........1212121212..........."
    "...........4343434343..........."
    ".............121212............."
    ".............434343............."
    "...............12..............."
    "...............43..............."
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
    "................................"
};

