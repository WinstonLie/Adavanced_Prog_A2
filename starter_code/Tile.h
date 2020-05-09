enum Types {
            Red = 'R',
            Yellow = 'Y',
            Dark_Blue = 'B',
            Light_Blue = 'L',
            Black = 'U',
            starter_player = 'S',
        };

class Tile{
    public:
        Tile();
        Tile(Types type);
        ~Tile();
        Types getType();

    private:
        Types type;
};