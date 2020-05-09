enum Types {
            Red,
            Yellow,
            Dark_Blue,
            Light_Blue,
            Black,
            starter_player,
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