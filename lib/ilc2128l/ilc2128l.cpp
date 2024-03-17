/*

	ILC2-12/8L emulation on 256x64 OLED

	svofski 2024

*/
#include "ilc2128l.h"
#include "sh1122.h"

constexpr int eggog_stride = 357;
constexpr int glyph_w = 21;
constexpr int glyph_h = 28;
constexpr int glyph9_h = 14;
constexpr int glyph_dot_y = 21;
constexpr int glyph_dot_h = 6;

// VFD glyph tilemap
extern uint8_t eggog_traced_pgm[];

static int dither_frame = 0;

int get_glyph_src_x(int c)
{
	if (c >= '0' && c <= '9') {
		return glyph_w * (c - '0'); 
	}
	else if (c >= 'A' && c <= 'F') {
		return glyph_w * (c - 'A' + 10);
	}
	else if (c == '-') {
		return glyph_w * 10; // fix with real '-' later
	}

	return glyph_w * 15;
}

#define DITHER 1

void copy_glyph(int src_x, int src_y, int dst_x, int dst_y, int src_h = glyph_h)
{
	for (int y = 0; y < src_h; ++y) {
		for (int x = 0; x < glyph_h; ++x) {
			int c = eggog_traced_pgm[(y + src_y) * eggog_stride + x + src_x] / 16;
			int ic = IndexedColor[c];
			#if DITHER
			if (c == 1) {
				if (1 & ((dither_frame + dst_x + x) ^ (dst_y + y))) {
					ic = 0;
				}
			}
			#endif
			Frame_DrawPixel(dst_x + x, dst_y + y, ic);
		}
	}
}

void draw_str(const char *m, const char *dots, int dst_y)
{
	int pos = 0;
	int dst_x = 0;

	// pos 0 has only "-" 
	int src_x = glyph_w * 16;
	int src_y = (m[pos] == '-' || m[pos] == 'A') ? 32 : 0;

	copy_glyph(src_x, src_y, dst_x, dst_y);
	++pos;
	dst_x += glyph_w;

	for (; pos < 12; ++pos, dst_x += glyph_w) {
		int src_x = get_glyph_src_x(m[pos]);
        bool dot = dots[pos] != 0;

		if (pos != 9) {
			src_y = dot ? 32 : 0;
			copy_glyph(src_x, src_y, dst_x, dst_y);
		}
		else {
			// special half-digit with fat minus for exponent sign and advanced eggoggery
			src_y = 64;
			copy_glyph(src_x, src_y, dst_x, dst_y); // copy the top half
		}

		if (pos == 9 && dot) {
			// copy dot at pos 9
			src_y = 64 + glyph_dot_y;
			src_x = 16 * glyph_w;
			copy_glyph(src_x, src_y, dst_x, dst_y + glyph_dot_y, glyph_dot_h);
		}
	}
}


ILC2128L::ILC2128L(int pin_cs, int pin_dc, int pin_rst) 
    : pin_cs(pin_cs), pin_dc(pin_dc), pin_rst(pin_rst) 
    {}

void ILC2128L::begin()
{
	SH1122_Config(pin_cs, pin_dc, pin_rst);
	Display_Init();
	Display_SetOrienation(OLED_DISP_NORMAL);
}

void ILC2128L::end()
{
    // TODO: shutdown SPI
}

void ILC2128L::set_digit(int pos, int digit, int dot)
{
    if (pos >= 0 && pos < 12) {
        display_chars[pos] = digit;
        display_dots[pos] = dot;
    }
}

void ILC2128L::refresh()
{
    ++dither_frame;
    Frame_Clear(0);
    draw_str(display_chars, display_dots, OLED_HEIGHT / 2  - glyph_h / 2);
	Display_SendFrame();
}