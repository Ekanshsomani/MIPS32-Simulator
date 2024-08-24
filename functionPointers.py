{
    "000000":
    {
        "100000": ADD,
        "100001": ADDU,
        "011011": SEB,
        "011011": SEH,
        "100010": SUB,
        "100011": SUBU,
        "000010": ROTR,
        "000110": ROTRV,
        "000000": SLL,
        "000100": SLLV,
        "000011": SRA,
        "000111": SRAV,
        "000010": SRL,
        "000110": SRLV,
        "100100": AND,
        "000000": NOP,
        "100111": NOR,
        "100101": OR,
        "100110": XOR,
        "001011": MOVN,
        "001010": MOVZ,
        "101010": SLT,
        "101011": SLTU,
        "011010": DIV,
        "011011": DIVU,
        "011000": MULT,
        "011001": MULTU,
        "010000": MFHI,
        "010010": MFLO,
        "010001": MTHI,
        "010011": MTLO,
        "001001": JALR,
        "001000": JR,
    },

    "001000": ADDI,
    "001001": ADDIU,

    "011100":
    {
        "100001": CLO,
        "100000": CLZ,
        "000000": MADD,
        "000001": MADDU,
        "000100": SUB,
        "000101": MSUBU,
        "000010": MUL,
    },

    "001111": LUI,
    "001100": ANDI,
    "001101": ORI,
    "001110": XORI,
    "001010": SLTI,
    "001011": SLTIU,
    "000111": BGTZ,
    "000110": BLEZ,
    "000010": J,
    "000011": JAL,

    "000101": BNE,
    # BNE is branch if not equal
    # BNEZ is branch if not equal to zero
    # so they can both be performed by same function
    # as rt is zero in later case.


    "000100": BEQ,
    # BEQZ and B will also work
    # as the req arguments are 
    # given

    "000001":
    {
        # 5 bit rt involved here
        "00000": BLTZ,
        "00001": BGEZ,
        "10000": BLTZAL,
        "10001": BGEZAL,
    }

    "100000": LB,
    "100100": LBU,
    "100001": LH,
    "100101": LHU,
    "100011": LW,
    "100010": LWL,
    "100110": LWR,
    "101000": SB,
    "101001": SH,
    "101011": SW,
    "101010": SWL,
    "101110": SWR,
    "110000": LL,
    "111000": SC,
}