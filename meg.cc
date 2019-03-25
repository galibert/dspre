#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>
#include <vector>


using u8 = unsigned char;
using u16 = unsigned short;
using s16 = signed short;
using u32 = unsigned int;
using u64 = unsigned long;

#if 0
constexpr u32 reverb_mask = 0x00000000;
constexpr u32 chorus_mask = 0x00000000;
constexpr u32 ins1_mask   = 0xffffffff;
constexpr u32 ins2_mask   = 0x00000000;
constexpr u32 var_mask    = 0x00000000;
#else
constexpr u32 reverb_mask = 0xffffffff;
constexpr u32 chorus_mask = 0xffffffff;
constexpr u32 ins1_mask   = 0xffffffff;
constexpr u32 ins2_mask   = 0xffffffff;
constexpr u32 var_mask    = 0xffffffff;
#endif

u8 bios[2097152];

u8 r8(u32 adr)
{
  return bios[adr];
}

u16 r16(u32 adr)
{
  return (bios[adr] << 8) | bios[adr+1];
}

u32 r24(u32 adr)
{
  return (bios[adr] << 16) |  (bios[adr+1] << 8) | bios[adr+2];
}

u32 r32(u32 adr)
{
  return (bios[adr] << 24) | (bios[adr+1] << 16) |  (bios[adr+2] << 8) | bios[adr+3];
}

u64 r64(u32 adr)
{
  return
    (u64(bios[adr]) << 56) | (u64(bios[adr+1]) << 48) |  (u64(bios[adr+2]) << 40) | (u64(bios[adr+3]) << 32) |
    (u64(bios[adr+4]) << 24) | (u64(bios[adr+5]) << 16) |  (u64(bios[adr+6]) << 8) | u64(bios[adr+7]);
}

const u8 *rp(u32 adr)
{
  return bios+adr;
}

struct ent {
  u16 adr;
  const char *name;
};

ent reverb[] = {
  { 0x000, "eq_filter_1a_c0" },
  { 0x001, "eq_filter_1a_c1" },
  { 0x002, "eq_filter_1a_c2" },
  { 0x003, "eq_filter_1a_c3" },
  { 0x004, "eq_filter_1a_c4" },

  { 0x007, "eq_filter_2a_c0" },
  { 0x006, "eq_filter_2a_c1" },
  { 0x005, "eq_filter_2a_c2" },
  { 0x008, "eq_filter_2a_c3" },
  { 0x009, "eq_filter_2a_c4" },

  { 0x00c, "eq_filter_3a_c0" },
  { 0x00b, "eq_filter_3a_c1" },
  { 0x00a, "eq_filter_3a_c2" },
  { 0x00d, "eq_filter_3a_c3" },
  { 0x00e, "eq_filter_3a_c4" },

  { 0x011, "eq_filter_4a_c0" },
  { 0x010, "eq_filter_4a_c1" },
  { 0x00f, "eq_filter_4a_c2" },
  { 0x012, "eq_filter_4a_c3" },
  { 0x013, "eq_filter_4a_c4" },

  { 0x016, "eq_filter_5a_c0" },
  { 0x015, "eq_filter_5a_c1" },
  { 0x014, "eq_filter_5a_c2" },
  { 0x017, "eq_filter_5a_c3" },
  { 0x018, "eq_filter_5a_c4" },

  { 0x02a, "fp47a"           },
  { 0x02b, "fp45a"           },
  { 0x02c, "fp46a"           },
  { 0x02d, "fp50a"           },
  { 0x02e, "fp48a"           },
  { 0x02f, "fp49a"           },

  { 0x036, "fp47b"           },
  { 0x037, "fp45b"           },
  { 0x038, "fp46b"           },
  { 0x039, "fp50b"           },
  { 0x03a, "fp48b"           },
  { 0x03b, "fp49b"           },

  { 0x049, "eq_filter_1b_c0" },
  { 0x048, "eq_filter_1b_c1" },
  { 0x047, "eq_filter_1b_c2" },
  { 0x04a, "eq_filter_1b_c3" },
  { 0x04b, "eq_filter_1b_c4" },

  { 0x04e, "eq_filter_2b_c0" },
  { 0x04d, "eq_filter_2b_c1" },
  { 0x04c, "eq_filter_2b_c2" },
  { 0x04f, "eq_filter_2b_c3" },
  { 0x050, "eq_filter_2b_c4" },

  { 0x053, "eq_filter_3b_c0" },
  { 0x052, "eq_filter_3b_c1" },
  { 0x051, "eq_filter_3b_c2" },
  { 0x054, "eq_filter_3b_c3" },
  { 0x055, "eq_filter_3b_c4" },

  { 0x058, "eq_filter_4b_c0" },
  { 0x057, "eq_filter_4b_c1" },
  { 0x056, "eq_filter_4b_c2" },
  { 0x059, "eq_filter_4b_c3" },
  { 0x05a, "eq_filter_4b_c4" },

  { 0x05d, "eq_filter_5b_c0" },
  { 0x05c, "eq_filter_5b_c1" },
  { 0x05b, "eq_filter_5b_c2" },
  { 0x05e, "eq_filter_5b_c3" },
  { 0x05f, "eq_filter_5b_c4" },

  { 0x076, "rev_t0_c2" },
  { 0x077, "rev_t0_c3" },
  { 0x078, "rev_t0_c0" },
  { 0x079, "rev_t1_c2" },
  { 0x07a, "rev_t1_c3" },
  { 0x07b, "rev_t1_c0" },
  { 0x07c, "rev_t0_c1" },
  { 0x07d, "rev_t2_c3" },
  { 0x07e, "rev_t2_c2" },
  { 0x07f, "rev_t2_c0" },
  { 0x080, "rev_t1_c1" },
  { 0x081, "rev_t3_c2" },
  { 0x082, "rev_t3_c3" },
  { 0x083, "rev_t3_c0" },
  { 0x084, "rev_t2_c1" },
  { 0x085, "rev_t4_c2" },
  { 0x086, "rev_t4_c3" },
  { 0x087, "rev_t4_c0" },
  { 0x088, "rev_t3_c1" },
  { 0x089, "rev_t5_c1" },
  { 0x08a, "rev_t5_c2" },
  { 0x08b, "rev_t5_c3" },
  { 0x08c, "rev_t4_c1" },

  { 0x08f, "master attenuation 1" },
  { 0x090, "master attenuation 2" },
  { 0x091, "rev_f5_c0" },

  { 0x029, "4000" },
  { 0x035, "4000" },
  { 0x028, "0000" },
  { 0x023, "2000" },
  { 0x024, "2000" },

  { 0x034, "fb_level_1" },
  { 0x040, "fb_level_2" },
  { }
};

ent reverb_int[] = {
  // 713fc
  { 0x12, "66d4" },
  { 0x11, "0000" },
  { 0x15, "04e8" },
  { 0x23, "08b9" },
  { 0x26, "0bf7" },
  { 0x25, "0ea0" },
  { 0x27, "11eb" },

  { 0x2a, "rev_t0_off0:14a2" },
  { 0x20, "rev_t0_off1" },
  { 0x0c, "rev_t0_off2" },
  { 0x14, "rev_t0_off3" },

  { 0x2c, "rev_t1_off0:267d" },
  { 0x21, "rev_t1_off1" },
  { 0x0d, "rev_t1_off2" },
  { 0x17, "rev_t1_off3" },

  { 0x2d, "rev_t2_off0:35ce" },
  { 0x22, "rev_t2_off1" },
  { 0x0e, "rev_t2_off2" },
  { 0x18, "rev_t2_off3" },

  { 0x2e, "rev_t3_off0:42ae" },
  { 0x24, "rev_t3_off1" },
  { 0x0f, "rev_t3_off2" },
  { 0x19, "rev_t3_off3" },

  { 0x30, "rev_t4_off0:4dfd" },
  { 0x28, "rev_t4_off1" },
  { 0x10, "rev_t4_off2" },
  { 0x1a, "rev_t4_off3" },

  { 0x31, "rev_t5_off0:56cc" },
  { 0x29, "rev_t5_off1" },
  { 0x13, "rev_t5_off2" },
  { 0x1b, "rev_t5_off3" },
  { }
};

// 6243e = chorus 1 setup

ent chorus_chorus[] = {
  { 0x098, "lfo_depth_1" }, // 26 40 55
  { 0x099, "4000" },
  { 0x09a, "filter_1a_c1" }, // 73 60
  { 0x09b, "filter_1a_c2" }, // 75 62
  { 0x09c, "filter_1a_c0" }, // 74 61
  { 0x09d, "filter_2a_c1" }, // 76 63
  { 0x09e, "filter_2a_c2" }, // 78 65
  { 0x09f, "filter_2a_c0" }, // 77 64
  { 0x0a0, "lfo_depth_3" },
  { 0x0a1, "4000" },
  { 0x0a2, "filter_1b_c1" }, // 73 60
  { 0x0a3, "filter_1b_c2" }, // 75 62
  { 0x0a4, "filter_1b_c0" }, // 74 61
  { 0x0a5, "filter_2b_c1" }, // 76 63
  { 0x0a6, "filter_2b_c2" }, // 78 65
  { 0x0a7, "filter_2b_c0" }, // 77 64
  { 0x0a8, "lfo_depth_4" },
  { 0x0a9, "0000" },
  { 0x0aa, "0000" },
  { 0x0ab, "chan1_left_input_level" }, // 79
  { 0x0ac, "chan1_right_input_level" }, // 80
  { 0x0ad, "fb_level_1"  }, // 66
  { 0x0ae, "0000" },
  { 0x0af, "0000" },
  { 0x0b0, "0000" },
  { 0x0b1, "0000" },
  { 0x0b2, "0000" },
  { 0x0b3, "lfo_depth_2" },
  { 0x0b4, "7fff" },
  { 0x0b5, "fb_level_2"  }, // 79
  { 0x0b6, "0000" },
  { 0x0b7, "0000" },
  { 0x0b8, "0000" },
  { 0x0b9, "5a00" },
  { 0x0ba, "0000" },
  { 0x0bb, "0000" },
  { 0x0bc, "0000" },
  { 0x0bd, "5a00" },
  { 0x0be, "0000" },
  { 0x0bf, "0000" },
  { }
};

ent *chorus_descs[3][2] = {
  { chorus_chorus, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr }
};

ent variation_auto_wah[] = {
  { 0x123, "lsf_c0" }, // 112 129
  { 0x121, "lsf_c1" }, // 111 128
  { 0x122, "lsf_c2" }, // 113 130
  { 0x126, "hsf_c0" }, // 115 132
  { 0x124, "hsf_c1" }, // 114 131
  { 0x125, "hsf_c2" }, // 116 133
  { 0x12e, "drywet1" }, // 185
  { 0x12f, "drywet2" }, // 186
  { 0x13e, "resonance_1" }, // 137
  { 0x142, "resonance_2" }, // 150
  { 0x14f, "cutoff_1" },    // 135
  { 0x133, "cutoff_2" },    // 134
  { }
};

ent *variation_descs[15][2] = {
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { variation_auto_wah, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
};

ent insertion1_chorus[] = {
  { 0x0c0, "lfo_depth_1" },
  { 0x0c1, "lfo_depth_2" },
  { 0x0c2, "4000" },
  { 0x0c3, "filter_1a_c1" }, // 73 60
  { 0x0c4, "filter_1a_c2" }, // 75 62
  { 0x0c5, "filter_1a_c0" }, // 74 61
  { 0x0c6, "filter_2a_c1" }, // 76 63
  { 0x0c7, "filter_2a_c2" }, // 78 65
  { 0x0c8, "filter_2a_c0" }, // 77 64
  { 0x0c9, "4000" },
  { 0x0ca, "filter_1b_c1" }, // 73 60
  { 0x0cb, "filter_1b_c2" }, // 75 62
  { 0x0cc, "filter_1b_c0" }, // 74 61
  { 0x0cd, "filter_2b_c1" }, // 76 63
  { 0x0ce, "filter_2b_c2" }, // 78 65
  { 0x0cf, "filter_2b_c0" }, // 77 64
  { 0x0d0, "0000" },
  { 0x0d1, "0000" },
  { 0x0d2, "lfo_depth_3" },
  { 0x0d3, "0800" },
  { 0x0d4, "0000" },
  { 0x0d5, "0000" },
  { 0x0d6, "0000" },
  { 0x0d7, "0000" },
  { 0x0d8, "0000" },
  { 0x0d9, "0000" },
  { 0x0da, "0000" },
  { 0x0db, "0000" },
  { 0x0dc, "0000" },
  { 0x0dd, "7fff" },
  { 0x0de, "0000" },
  { 0x0df, "0000" },
  { 0x0e0, "7fff" },
  { 0x0e1, "fb_level_1" },
  { 0x0e2, "0000" },
  { 0x0e3, "chan1_left_input_level" }, // 79
  { 0x0e4, "chan1_right_input_level" }, // 80
  { 0x0e5, "fb_level_2" },
  { 0x0e6, "0000" },
  { 0x0e7, "0000" },
  { 0x0e8, "0000" },
  { 0x0e9, "7fff" },
  { 0x0ea, "dry_1" },
  { 0x0eb, "wet_1" },
  { 0x0ec, "dry_2" },
  { 0x0ed, "wet_2" },
  { 0x0ee, "0800" },
  { 0x0ef, "0000" },
  { }
};

ent insertion1_chorus_int[] = {
  { 0x40, "0000" },
  { 0x41, "0086" },
  { 0x42, "0086" },
  { 0x43, "00c6" },
  { 0x44, "00c6" },
  { 0x45, "00c6" },
  { 0x46, "00c6" },
  { 0x47, "0086" },
  { 0x48, "0086" },
  { 0x49, "0000" },
  { 0x4a, "0000" },
  { 0x4b, "0000" },
  { 0x4c, "0000" },
  { 0x4d, "0000" },
  { 0x4e, "0001" },
  { 0x4f, "0000" },
  { }
};

ent insertion2_chorus[] = {
  { 0x0f0, "lfo_depth_1" },
  { 0x0f1, "lfo_depth_2" },
  { 0x0f2, "4000" },
  { 0x0f3, "filter_1a_c1" }, // 73 60
  { 0x0f4, "filter_1a_c2" }, // 75 62
  { 0x0f5, "filter_1a_c0" }, // 74 61
  { 0x0f6, "filter_2a_c1" }, // 76 63
  { 0x0f7, "filter_2a_c2" }, // 78 65
  { 0x0f8, "filter_2a_c0" }, // 77 64
  { 0x0f9, "4000" },
  { 0x0fa, "filter_1b_c1" }, // 73 60
  { 0x0fb, "filter_1b_c2" }, // 75 62
  { 0x0fc, "filter_1b_c0" }, // 74 61
  { 0x0fd, "filter_2b_c1" }, // 76 63
  { 0x0fe, "filter_2b_c2" }, // 78 65
  { 0x0ff, "filter_2b_c0" }, // 77 64
  { 0x100, "0000" },
  { 0x101, "0000" },
  { 0x102, "lfo_depth_3" },
  { 0x103, "0800" },
  { 0x104, "0000" },
  { 0x105, "0000" },
  { 0x106, "0000" },
  { 0x107, "0000" },
  { 0x108, "0000" },
  { 0x109, "0000" },
  { 0x10a, "0000" },
  { 0x10b, "0000" },
  { 0x10c, "0000" },
  { 0x10d, "7fff" },
  { 0x10e, "0000" },
  { 0x10f, "0000" },
  { 0x110, "7fff" },
  { 0x111, "fb_level_1" },
  { 0x112, "0000" },
  { 0x113, "chan1_left_input_level" }, // 79
  { 0x114, "chan1_right_input_level" }, // 80
  { 0x115, "fb_level_2" },
  { 0x116, "0000" },
  { 0x117, "0000" },
  { 0x118, "0000" },
  { 0x119, "7fff" },
  { 0x11a, "dry_1" },
  { 0x11b, "wet_1" },
  { 0x11c, "dry_2" },
  { 0x11d, "wet_2" },
  { 0x11e, "0800" },
  { 0x11f, "0000" },
  { }
};

// lfo 0,2,c phase 0.5156, 0, 0.0156

ent *insertion1_descs[11][2] = {
  { insertion1_chorus, insertion1_chorus_int },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
};

ent *insertion2_descs[11][2] = {
  { insertion2_chorus, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
  { nullptr, nullptr },
};

u32 b(u64 opc, u32 start, u32 count)
{
  return (opc >> start) & ((1 << count) - 1);
}

u64 t[3] = {0, 0, 0};


// Current state of the investigations:
// The MEG as integrated in the swp30 has 384 program steps.
//
// In the mu100 the 384 steps are split as such, and each part
// individually uploaded/updated:
// 000-097: reverb + main eq and mixing
// 098-0bf: chorus
// 0c0-0ef: insertion 1
// 0f0-11f: insertion 2
// 120-17f: variation
//
// An opcode is 64 bits.  It is accompanied by a 16 bits fixed-point
// constant (2.14 signed, e.g. 16384 is 1, -16384 is -1).
//
// Instructions with an address multiple of 3 can do a reverb memory
// access.  They're accompanied by a 16-bits constant integer offset.
//
// So the internal program memory is (1 qword + 1word)*384 + 1word * 128
//
// There are 256 internal "rotating" registers, and 64 non-rotating one.
//
// Registers are probably 18 bits, 2.16 fixed point.  We'll call the
// rotating registers r<nn> and the non-rotating m<nn>.
//
// Each instruction executes in one cycle, all 384 instructions
// execute once every sample, there are no control-flow instructions
// nor tests afaict.
//
// The rotating registers and the reverb memory rotate every sample
// (e.g. on pc==0 or something similar).  The external reverb memory
// rotates too (e.g. an offset is (in?)cremented).  The rotating
// registers virtually rotate such as register r10 becomes r11 at the
// next sample, r12 at the following one, etc.  Very useful for FIR
// filters.
//
// The external memory is divided in 8 banks, of which 5 are used in the mu100:
// map 0: start = 000000 size = 010000 base = 0   (reverb)
// map 1: start = 010000 size = 008000 base = d   (chorus)
// map 2: start = 028000 size = 010000 base = 10  (insertion 1)
// map 3: start = 038000 size = 008000 base = 14  (insertion 2)
// map 4: start = 018000 size = 010000 base = 18  (variation)
//
// The base information indicates the pc divided by 4*3 at which this
// bank starts to be used (0, 9c, c0, f0, 120).
//
// There also are 24 lfo registers, that produce a triangle wave at a
// pitch and phase determined by the main cpu. They may be updated for
// each sample, or maybe when they're read.  Each used one seems to be
// only read once, so both methods are possible.
//
// LFO register usage map (the reverb doesn't use any):
//   chorus:      08-0b
//   insertion 1: 00-03 0c-0e
//   insertion 2: 04-07 0f-11
//   variation:   12-17
//
// This seems to be slightly correlated with addresses but the
// accesses are sometimes back-to-back so nothing is obvious.
//
// The instruction encoding is vliw-ish.  One instruction can:
// - Read from one r and one m register.
// - Do an unclear number of adds
// - Do one multiply
// - Write to one r and one m register.
// - Read/write to the product/accumulator register (write then read, other registers are read then write)
// - Read/write to the memory buffer
// - Read and possibly step a lfo register
// - Every instruction where pc % 3 == 0 can initiate a memory access.  Read results are available two cycles after.
// 
// Instruction structure:
//
// 33333333 33333333 22222222 22222222 11111111 11111111 00000000 00000000
// fedcba98 76543210 fedcba98 76543210 fedcba98 76543210 fedcba98 76543210
//
// 66665555 55555544 44444444 33333333 33222222 22221111 11111100 00000000
// 32109876 54321098 76543210 98765432 10987654 32109876 54321098 76543210
// -LB----- -rrrrrrr r--mmmmm m-MM---- -P---*** -----Arr rrrrrrmm mmmm----
//
// Bit functions by number, in decimal:
// 04-09: m register to read
// 10-17: r register to read
// 18   : select r or m when single source
// 24   : do a multiplication
// 25-26: multiplcation mode
// 30   : use p as source for write
// 36-37: memory access mode
// 39-44: m register to write
// 46   : select r or m to write from p (if b61 is unset)
// 47-54: r register to write
// 61   : write to memory buffer
// 62   : a lfo is read
// 
//
// multiplication mode, active when b24=1, uses the fixed-point constant
// 0: p  = fp * reg (r or m is selected by b18)
// 1: p  = fp * (r+m) or something similar
// 2: p  = fp * (r+m) or something similar
// 3: p += fp * reg (r or m is selected by b18)
//
// The operation on 1 & 2 is unclear, but something that uses both
// input registers and fp.  Could be fp*a+b for instance, or even
// something else.
//
// On op 1&2 b18 is sometimes set and sometimes not, so either the
// operation is assymetric or it means something else.
//
// When b24=0 the value in the multiplication mode bits varies, so
// it's setting up an operation too.  It could just be that the
// operation number is 3 bits, but that doesn't tell us what the other
// four are.
//
// It seems that the m registers is supposed to be written if b46=1 or
// b47=1.  And yes, b47 is the bottom bit of the r register number, go
// figure.  In particular the moves from the memory buffer to a m
// register usually have b47 set.
//
// Memory access mode is 1=read, 2=write, 3=read at address+1 for lfo
// interpolation.
// 
// Bit 62 is set when a lfo register is read.  *which* lfo register is
// not understood.  The multiplier is always active and in mode 0, and
// the fp constant is the lfo amplitude as set by the main program.
// 
// What is done with the value in p after the lfo is multiplied by the
// amplitude is unclear.  The integer part should be added to the
// offset.  The fractional part needs to be used for interpolation.
// We can see that there's not long after the lfo computation two
// reads, one in mode 1 and one in mode 3 to two different registers.
// There's then two computations, one mul of type 2 with constant 0,
// r00 and the m register of the first read, then another one in mode
// 3, constant still 0 and the second register.  That somehow applies
// the interpolation, using either c = (1-frac)*a + frac*b or c = a +
// frac*(b-a).  The first version seems the most probable.
//
// Bit 63 is used in the lo-fi variation only, which doesn't help.


void dump(std::string name, u32 address, u16 start, u16 len, ent *fp, ent *in)
{
  printf("  %s:\n", name.c_str());
  for(int i=0; i<len; i++) {
    u64 opc = r64(address+8*i);
    t[(start+i) % 3] |= opc;
    static char anb[32], inb[32];
    sprintf(anb, "fp%03x", start+i);
    sprintf(inb, "of%03x", (start+i)/3);
    const char *aname = anb, *iname = inb;
    if(fp)
      for(int j=0; fp[j].name; j++)
	if(start+i == fp[j].adr) {
	  aname = fp[j].name;
	  break;
	}

    if(in)
      for(int j=0; in[j].name; j++)
	if((start+i)/3 == in[j].adr) {
	  iname = in[j].name;
	  break;
	}

    char *p;
    u32 val = strtol(aname, &p, 16);
    if(p == aname+4 && !*p) {
      sprintf(anb, "%f", s16(val)/16384.0);
      aname = anb;
    }

    printf("%03x: %016lx [47:r%02x 39:m%02x 10:r%02x 4:m%02x - 55:%03x 45:%x 19:%04x 0:%x]",
	   start+i, opc,
	   b(opc, 47, 8), b(opc, 39, 6), b(opc, 10, 8), b(opc, 4, 6),
	   b(opc, 55, 6), b(opc, 45, 2), b(opc, 19, 14), b(opc, 0, 4));

    if(b(opc, 62, 1))
      printf(" lfo");

    if(b(opc, 23, 1))
      switch(b(opc, 24, 2)) {
      case 0:
	if(b(opc, 18, 1))
	  printf(" [p += %s * m%02x]", aname, b(opc,  4, 6));
	else
	  printf(" [p += %s * r%02x]", aname, b(opc, 10, 8));
	break;
      case 1:
	printf(" [p ?1= %s * (r%02x + m%02x)]", aname, b(opc, 10, 8), b(opc,  4, 6));
	break;
      case 2:
	printf(" [p ?2= %s * (r%02x + m%02x)]", aname, b(opc, 10, 8), b(opc,  4, 6));
	break;
      case 3:
	if(b(opc, 18, 1))
	  printf(" [p = %s * m%02x]", aname, b(opc,  4, 6));
	else
	  printf(" [p = %s * r%02x]", aname, b(opc, 10, 8));
	break;
      }

    if(b(opc, 30, 1)) {
      if(b(opc, 61, 1))
	printf(" [mbuf = p]");
      else if(b(opc, 46, 1) == 1)
	printf(" [m%02x = p]", b(opc, 39, 6));
      else
	printf(" [r%02x = p]", b(opc, 47, 8));
    } else if(b(opc, 46, 1) == 1)
      printf(" [m%02x = ?%d]", b(opc, 39, 6), b(opc, 45, 1));


    if(b(opc, 36, 2)) {
      static const char *modes[4] = { nullptr, "w", "r", "r+1" };
      int mode = b(opc, 36, 2);
      
      printf(" [mem %s %x %s", modes[mode], b(opc, 33, 3), iname);
      if(mode & 2)
	printf(" -> m%02x (%02x)", b(r64(address+8*(i+2)), 39, 6), b(r64(address+8*(i+2)), 47, 8));
      printf("]");
    }

    printf("\n");
  }
  printf("\n");
}

int main()
{
  FILE *fd = fopen("mu100.bin", "rb");
  fread(bios, sizeof(bios), 1, fd);
  fclose(fd);

  if(reverb_mask & 1)
    dump("reverb", 0x8c56c, 0, 0x98, reverb, reverb_int);

  for(int i=0; i<3; i++) {
    static const char *names[3] = { "chorus", "phaser", "ens detune" };
    if(chorus_mask & (1<<i)) {
      std::string s = std::string("chorus ") + names[i];
      dump(s, 0x8ca2c + 0x140*i, 0x98, 0x28, chorus_descs[i][0], chorus_descs[i][1]);
    }
  }

  for(int i=0; i<15; i++) {
    static const char *names[15] = { "delay", "ambiance", "phaser", "er", "wah", "distortion", "rooms", "ens detune", "?8", "?9", "talk mod", "lo-fi", "?12", "wah+dist+delay", "dist+delay" };
    if(var_mask & (1 << i)) {
      std::string s = std::string("variation ") + names[i];
      dump(s, 0x8cdec + 0x300*i, 0x120, 0x60, variation_descs[i][0], variation_descs[i][1]);
    }
  }

  for(int i=0; i<11; i++) {
    static const char *names[11] = { "chorus", "speaker", "distortion", "aural", "wah", "phaser", "ens detune", "eq", "delay", "karaoke", "rooms" };
    if(ins1_mask & (1 << i)) {
      std::string s = std::string("insertion1 ") + names[i];
      dump(s, 0x8faec + 0x180*i, 0xc0, 0x30, insertion1_descs[i][0], insertion1_descs[i][1]);
    }
  }

  for(int i=0; i<11; i++) {
    static const char *names[11] = { "chorus", "speaker", "distortion", "aural", "wah", "phaser", "ens detune", "eq", "delay", "karaoke", "rooms" };
    if(ins2_mask & (1 << i)) {
      std::string s = std::string("insertion2 ") + names[i];
      dump(s, 0x90b6c + 0x180*i, 0xf0, 0x30, insertion2_descs[i][0], insertion2_descs[i][1]);
    }
  }

  fprintf(stderr, "%016lx %016lx %016lx\n", ~t[0], ~t[1], ~t[2]);
  return 0;
}

