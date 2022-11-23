

using U64 = unsigned long long;

class Bitboard
{
  private:
    U64 bitboard;
  public:
    // constructors
    Bitboard(); // default constructor
    Bitboard(const U64); // constructor
    Bitboard(const Bitboard&); // copy constructor

    // user-defined conversion functions
    operator U64() const;
    operator U64&();

    // Bitboard operations
    void set_bit(const int);
    void clear_bit(const int);
    bool get_bit(const int) const;
    void invert_bit(const int);
    void pop_bit(void);
    int count_set_bits(void) const;
    int get_ls1b_index(void) const;
    void print_bitboard(void) const;
    void clear_bitboard(void);
};
