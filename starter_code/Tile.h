class Tile{
    public:
        Tile();
        Tile(int type);
        ~Tile();
        Tile getType();

    private:
        enum Types {
            Red,
            Yellow,
            Dark_Blue,
            Light_Blue,
            Black,
            starter_player,

        };

        Types type;
};