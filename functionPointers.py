# Creating a dic to see how decoding would work

{
    # op code
    "0" :
    {
        # func
        "0" : ["SLL"],

        "2" : ["ROTR", "SRL"],

        "3" : ["SRA"],

        "4" : ["SLLV"],

        "5" : ["LSA"],

        "6" : ["ROTRV", "SRLV"],

        "7" : ["SRAV"],

        "9" : ["JALR", "JALR.HB"], # msb of shamt is index

        "16" : ["CLZ"],

        "17" : ["CLO"],

        "32" : ["ADD"],

        "33" : ["ADDU"],

        "34" : ["SUB"],

        "35" : ["SUBU"],

        "36" : ["AND"],

        "37" : ["OR"],

        "38" : ["XOR"],

        "39" : ["NOR"],

        "42" : ["SLT"],

        "43" : ["SLTU"],

        # list index can be obtained by doing shamt-2 in belowcases
        "48" : ["MUL", "MUH"],

        "49" : ["MULU", "MUHU"],

        "50" : ["DIV", "MOD"],

        "51" : ["DIVU", "MODU"],
    },

    "1" : ["BGEZ", "BLTZ"],

    "2" : ["J"],

    "3" : ["JAL"],

    "4" : ["BEQ"],

    "5" : ["BNE"],

    "6" : ["BLEZ", "BGEUC", "BLEZALC", "BGEZALC"],
    # BLEZ -> rt = 0
    # BGEUC, BLTUC, rs != rt != 0
    # BLEZALC rs = 0, rt != 0
    # BGEZALC rs = rt != 0

    "7" : ["BGTZ", "BLTUC", "BGTZALC", "BLTZALC"],

    "8" : ["BEQC", "BOVC"],

    "9" : ["ADDIU"],

    "10" : ["SLTI"],

    "11" : ["SLTIU"],

    "12" : ["ANDI"],

    "13" : ["ORI"],

    "14" : ["XORI"],

    "15" : ["AUI"],

    "22" : ["BGEC"],

    "23" : ["BLTC"],

    "24" : ["BNEC", "BNVC"],

    "31" :
    {
        # func

        "32" : ["ALIGN", "BITSWAP"] 
        # an extremely specific case of division, check README

    },

    "50" : ["BC"],

    "54" : ["JIC", "BEQZC"],

    "58" : ["BALC"],

    "59" : ["ADDIUPC", "AUIPC", "ALUIPC"],

    "62" : ["JIALC", "BNEZC"],
}

# Below as an earlier attempt
# {
#     "000000":
#     {
#         "100000": ADD,
#         "100001": ADDU,
#         "011011": SEB,
#         "011011": SEH,
#         "100010": SUB,
#         "100011": SUBU,
#         "000010": ROTR,
#         "000110": ROTRV,
#         "000000": SLL,
#         "000100": SLLV,
#         "000011": SRA,
#         "000111": SRAV,
#         "000010": SRL,
#         "000110": SRLV,
#         "100100": AND,
#         "000000": NOP,
#         "100111": NOR,
#         "100101": OR,
#         "100110": XOR,
#         "001011": MOVN,
#         "001010": MOVZ,
#         "101010": SLT,
#         "101011": SLTU,
#         "011010": DIV,
#         "011011": DIVU,
#         "011000": MULT,
#         "011001": MULTU,
#         "010000": MFHI,
#         "010010": MFLO,
#         "010001": MTHI,
#         "010011": MTLO,
#         "001001": JALR,
#         "001000": JR,
#     },

#     "001000": ADDI,
#     "001001": ADDIU,

#     "011100":
#     {
#         "100001": CLO,
#         "100000": CLZ,
#         "000000": MADD,
#         "000001": MADDU,
#         "000100": SUB,
#         "000101": MSUBU,
#         "000010": MUL,
#     },

#     "011111":
#     {
#         "000000": EXT,
#         "000100": INS,
#         "100000": WSBH,
#     },

#     "001111": LUI,
#     "001100": ANDI,
#     "001101": ORI,
#     "001110": XORI,
#     "001010": SLTI,
#     "001011": SLTIU,
#     "000111": BGTZ,
#     "000110": BLEZ,
#     "000010": J,
#     "000011": JAL,

#     "000101": BNE,
#     # BNE is branch if not equal
#     # BNEZ is branch if not equal to zero
#     # so they can both be performed by same function
#     # as rt is zero in later case.


#     "000100": BEQ,
#     # BEQZ and B will also work
#     # as the req arguments are 
#     # given

#     "000001":
#     {
#         # 5 bit rt involved here
#         "00000": BLTZ,
#         "00001": BGEZ,
#         "10000": BLTZAL,
#         "10001": BGEZAL,
#     }

#     "100000": LB,
#     "100100": LBU,
#     "100001": LH,
#     "100101": LHU,
#     "100011": LW,
#     "101000": SB,
#     "101001": SH,
#     "101011": SW,
#     "110000": LL,
#     "111000": SC,
# }