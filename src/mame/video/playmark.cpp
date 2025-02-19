// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Pierpaolo Prazzoli, Quench
#include "emu.h"
#include "includes/playmark.h"
#include "screen.h"


/***************************************************************************

  Callbacks for the TileMap code

***************************************************************************/

TILE_GET_INFO_MEMBER(playmark_state::bigtwin_get_tx_tile_info)
{
	u16 code = m_videoram[0][2 * tile_index];
	u16 color = m_videoram[0][2 * tile_index + 1];
	tileinfo.set(2, code, color, 0);
}

TILE_GET_INFO_MEMBER(playmark_state::bigtwin_get_fg_tile_info)
{
	u16 code = m_videoram[1][2 * tile_index];
	u16 color = m_videoram[1][2 * tile_index + 1];
	tileinfo.set(1, code, color, 0);
}


TILE_GET_INFO_MEMBER(playmark_state::wbeachvl_get_tx_tile_info)
{
	u16 code = m_videoram[0][2 * tile_index];
	u16 color = m_videoram[0][2 * tile_index + 1];

	tileinfo.set(2, code, (color >> 2), 0);
}

TILE_GET_INFO_MEMBER(playmark_state::wbeachvl_get_fg_tile_info)
{
	u16 code = m_videoram[1][2 * tile_index];
	u16 color = m_videoram[1][2 * tile_index + 1];

	tileinfo.set(1, (code & 0x7fff), (color >> 2) + 8, (code & 0x8000) ? TILE_FLIPX : 0);
}

TILE_GET_INFO_MEMBER(playmark_state::wbeachvl_get_bg_tile_info)
{
	u16 code = m_videoram[2][2 * tile_index];
	u16 color = m_videoram[2][2 * tile_index + 1];

	tileinfo.set(1, (code & 0x7fff), (color >> 2), (code & 0x8000) ? TILE_FLIPX : 0);
}


TILE_GET_INFO_MEMBER(playmark_state::hrdtimes_get_tx_tile_info)
{
	int code = m_videoram[0][tile_index] & 0x0fff;
	int colr = m_videoram[0][tile_index] & 0xe000;

	tileinfo.set(3, code, (colr >> 13), 0);
}

TILE_GET_INFO_MEMBER(playmark_state::hrdtimes_get_fg_tile_info)
{
	int code = m_videoram[1][tile_index] & 0x1fff;
	int colr = m_videoram[1][tile_index] & 0xe000;

	tileinfo.set(2, code, (colr >> 13) + 8, 0);
}

TILE_GET_INFO_MEMBER(playmark_state::hrdtimes_get_bg_tile_info)
{
	int code = m_videoram[2][tile_index] & 0x1fff;
	int colr = m_videoram[2][tile_index] & 0xe000;

	tileinfo.set(1, code, (colr >> 13), 0);
}


TILE_GET_INFO_MEMBER(playmark_state::bigtwinb_get_tx_tile_info)
{
	int code = m_videoram[0][tile_index] & 0x0fff;
	int colr = m_videoram[0][tile_index] & 0xf000;

	tileinfo.set(3, code, (colr >> 12), 0);
}

/***************************************************************************

  Start the video hardware emulation.

***************************************************************************/

VIDEO_START_MEMBER(playmark_state,bigtwin)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::bigtwin_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 32);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::bigtwin_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);

	m_xoffset = 0;
	m_yoffset = 0;

	m_pri_masks[0] = 0;
	m_pri_masks[1] = 0;
	m_pri_masks[2] = 0;
}


VIDEO_START_MEMBER(playmark_state,bigtwinb)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::bigtwinb_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 64);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);
	m_fg_tilemap->set_transparent_pen(0);

	m_bg_tilemap->set_scrolldx(-4, -4);

	m_xoffset = 1;
	m_yoffset = 0;

	m_pri_masks[0] = 0;
	m_pri_masks[1] = 0;
	m_pri_masks[2] = 0;
}


VIDEO_START_MEMBER(playmark_state,wbeachvl)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::wbeachvl_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 32);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::wbeachvl_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 64, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::wbeachvl_get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 64, 32);

	m_tx_tilemap->set_transparent_pen(0);
	m_fg_tilemap->set_transparent_pen(0);

	m_xoffset = 0;
	m_yoffset = 0;

	m_pri_masks[0] = 0xfff0;
	m_pri_masks[1] = 0xfffc;
	m_pri_masks[2] = 0;
}

VIDEO_START_MEMBER(playmark_state,excelsr)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::bigtwin_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::bigtwin_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);

	m_xoffset = 0;
	m_yoffset = 0;

	m_pri_masks[0] = 0;
	m_pri_masks[1] = 0xfffc;
	m_pri_masks[2] = 0xfff0;
}

VIDEO_START_MEMBER(playmark_state,hotmind)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 64);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);
	m_fg_tilemap->set_transparent_pen(0);

	m_tx_tilemap->set_scrolldx(-14, -14);
	m_fg_tilemap->set_scrolldx(-14, -14);
	m_bg_tilemap->set_scrolldx(-14, -14);

	m_xoffset = -9;
	m_yoffset = -8;

	m_pri_masks[0] = 0xfff0;
	m_pri_masks[1] = 0xfffc;
	m_pri_masks[2] = 0;
}

VIDEO_START_MEMBER(playmark_state,luckboomh)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 64);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_fg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);
	m_fg_tilemap->set_transparent_pen(0);

	m_tx_tilemap->set_scrolldx( -9,  -9);
	m_fg_tilemap->set_scrolldx(-11, -11);
	m_bg_tilemap->set_scrolldx(-13, -13);

	m_xoffset = -9;
	m_yoffset = -8;

	m_pri_masks[0] = 0xfff0;
	m_pri_masks[1] = 0xfffc;
	m_pri_masks[2] = 0;
}



// Hard Times level 2-4 boss(truck) needs this.. or something similar.
#define TILES_PER_PAGE_Y    (0x20)
#define TILES_PER_PAGE_X    (0x20)
#define PAGES_PER_TMAP_Y    (0x1)
#define PAGES_PER_TMAP_X    (0x4)

TILEMAP_MAPPER_MEMBER(playmark_state::playmark_tilemap_scan_pages)
{
	return  (col / TILES_PER_PAGE_X) * TILES_PER_PAGE_Y * TILES_PER_PAGE_X * PAGES_PER_TMAP_Y +
			(col % TILES_PER_PAGE_X) +

			(row / TILES_PER_PAGE_Y) * TILES_PER_PAGE_Y * TILES_PER_PAGE_X +
			(row % TILES_PER_PAGE_Y) * TILES_PER_PAGE_X;
}

// there's enough ram for 64*128 on each tilemap..

VIDEO_START_MEMBER(playmark_state,hrdtimes)
{
	m_tx_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_tx_tile_info)), TILEMAP_SCAN_ROWS, 8, 8, 64, 64);
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_fg_tile_info)), tilemap_mapper_delegate(*this, FUNC(playmark_state::playmark_tilemap_scan_pages)), 16, 16, 128, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(playmark_state::hrdtimes_get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 32, 32);

	m_tx_tilemap->set_transparent_pen(0);
	m_fg_tilemap->set_transparent_pen(0);

	m_tx_tilemap->set_scrolldx(-14, -14);
	m_fg_tilemap->set_scrolldx(-10, -10);
	m_bg_tilemap->set_scrolldx(-12, -12);

	m_xoffset = -8;
	m_yoffset = -8;

	m_pri_masks[0] = 0xfff0;
	m_pri_masks[1] = 0xfffc;
	m_pri_masks[2] = 0;
}

/***************************************************************************

  Memory handlers

***************************************************************************/

void playmark_state::wbeachvl_txvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[0][offset]);
	m_tx_tilemap->mark_tile_dirty(offset / 2);
}

void playmark_state::wbeachvl_fgvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[1][offset]);
	m_fg_tilemap->mark_tile_dirty(offset / 2);
}

void playmark_state::wbeachvl_bgvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[2][offset]);
	m_bg_tilemap->mark_tile_dirty(offset / 2);
}

void playmark_state::hrdtimes_txvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[0][offset]);
	m_tx_tilemap->mark_tile_dirty(offset);
}

void playmark_state::hrdtimes_fgvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[1][offset]);
	m_fg_tilemap->mark_tile_dirty(offset);
}

void playmark_state::hrdtimes_bgvideoram_w(offs_t offset, u16 data, u16 mem_mask)
{
	COMBINE_DATA(&m_videoram[2][offset]);
	m_bg_tilemap->mark_tile_dirty(offset);
}

void playmark_state::bigtwin_scroll_w(offs_t offset, u16 data, u16 mem_mask)
{
	data = COMBINE_DATA(&m_scroll[offset]);

	switch (offset)
	{
		case 0: m_tx_tilemap->set_scrollx(0, data + 2); break;
		case 1: m_tx_tilemap->set_scrolly(0, data); break;
		case 2: m_bgscrollx = -(data + 4); break;
		case 3: m_bgscrolly = (-data) & 0x1ff;
				m_bg_enable = BIT(data, 9);
				m_bg_full_size = BIT(data, 10);
				break;
		case 4: m_fg_tilemap->set_scrollx(0, data + 6); break;
		case 5: m_fg_tilemap->set_scrolly(0, data); break;
	}
}

void playmark_state::wbeachvl_scroll_w(offs_t offset, u16 data, u16 mem_mask)
{
	data = COMBINE_DATA(&m_scroll[offset]);

	switch (offset)
	{
		case 0: m_tx_tilemap->set_scrollx(0, data + 2); break;
		case 1: m_tx_tilemap->set_scrolly(0, data); break;
		case 2: m_fgscrollx = data + 4; break;
		case 3: m_fg_tilemap->set_scrolly(0, data & 0x3ff);
				m_fg_rowscroll_enable = BIT(data, 11);
				break;
		case 4: m_bg_tilemap->set_scrollx(0, data + 6); break;
		case 5: m_bg_tilemap->set_scrolly(0, data); break;
	}
}

void playmark_state::excelsr_scroll_w(offs_t offset, u16 data, u16 mem_mask)
{
	data = COMBINE_DATA(&m_scroll[offset]);

	switch (offset)
	{
		case 0: m_tx_tilemap->set_scrollx(0, data + 2); break;
		case 1: m_tx_tilemap->set_scrolly(0, data); break;
		case 2: m_bgscrollx = -data; break;
		case 3: m_bgscrolly = (-data + 2) & 0x1ff;
				m_bg_enable = BIT(data, 9);
				m_bg_full_size = BIT(data, 10);
				break;
		case 4: m_fg_tilemap->set_scrollx(0, data + 6); break;
		case 5: m_fg_tilemap->set_scrolly(0, data);   break;
	}
}

void playmark_state::hrdtimes_scroll_w(offs_t offset, u16 data, u16 mem_mask)
{
	data = COMBINE_DATA(&m_scroll[offset]);

	switch (offset)
	{
		case 0: m_tx_tilemap->set_scrollx(0, data); break;
		case 1: m_tx_tilemap->set_scrolly(0, data); break;
		case 2: m_fg_tilemap->set_scrollx(0, data); break;
		case 3: m_fg_tilemap->set_scrolly(0, data); break;
		case 4: m_bg_tilemap->set_scrollx(0, data); break;
		case 5: m_bg_tilemap->set_scrolly(0, data); break;
	}
}

/***************************************************************************

  Display refresh

***************************************************************************/

void playmark_state::draw_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int codeshift )
{
	int offs, start_offset = m_spriteram.bytes() / 2 - 4;
	int height = m_gfxdecode->gfx(0)->height();
	int colordiv = m_gfxdecode->gfx(0)->granularity() / 16;

	// find the "end of list" to draw the sprites in reverse order
	for (offs = 4; offs < m_spriteram.bytes() / 2; offs += 4)
	{
		if (m_spriteram[offs + 3 - 4] == 0x2000) // end of list marker
		{
			start_offset = offs - 4;
			break;
		}
	}

	for (offs = start_offset; offs >= 4; offs -= 4)
	{
		int sy = m_spriteram[offs + 3 - 4];   // -4? what the... ???

		int flipx = sy & 0x4000;
		int sx = (m_spriteram[offs + 1] & 0x01ff) - 16 - 7;
		sy = (256 - 8 - height - sy) & 0xff;
		int code = m_spriteram[offs + 2] >> codeshift;
		int color = ((m_spriteram[offs + 1] & 0x3e00) >> 9) / colordiv;
		int pri = (m_spriteram[offs + 1] & 0x8000) >> 15;

		if(!pri && (color & 0x0c) == 0x0c)
			pri = 2;

		m_gfxdecode->gfx(0)->prio_transpen(bitmap,cliprect,
					code,
					color,
					flipx,0,
					sx + m_xoffset,sy + m_yoffset,
					screen.priority(),m_pri_masks[pri],m_sprtranspen);
	}
}


void playmark_state::bigtwinb_draw_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int codeshift )
{
	int offs, start_offset = m_spriteram.bytes() / 2 - 4;
	int height = m_gfxdecode->gfx(0)->height();

	// find the "end of list" to draw the sprites in reverse order
	for (offs = 4; offs < m_spriteram.bytes() / 2; offs += 4)
	{
		if (m_spriteram[offs + 3 - 4] == 0x2000) // end of list marker
		{
			start_offset = offs - 4;
			break;
		}
	}

	for (offs = start_offset; offs >= 4; offs -= 4)
	{
		int sy = m_spriteram[offs + 3 - 4];   // -4? what the... ???

		int flipx = sy & 0x4000;
		int sx = (m_spriteram[offs + 1] & 0x01ff) - 16 - 7;
		sy = (256 - 8 - height - sy) & 0xff;
		int code = m_spriteram[offs + 2] >> codeshift;
		int color = ((m_spriteram[offs + 1] & 0xf000) >> 12);

		m_gfxdecode->gfx(0)->transpen(bitmap,cliprect,
					code,
					color,
					flipx,0,
					sx + m_xoffset,sy + m_yoffset, m_sprtranspen);
	}
}

void playmark_state::draw_bitmap( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect )
{
	int count = 0;
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			int const color = m_bgvideoram[count] & 0xff;

			if (color)
			{
				if (m_bg_full_size)
				{
					bitmap.pix((y + m_bgscrolly) & 0x1ff, (x + m_bgscrollx) & 0x1ff) = 0x100 + color;

					u8 *const pri = &screen.priority().pix((y + m_bgscrolly) & 0x1ff);
					pri[(x + m_bgscrollx) & 0x1ff] |= 2;
				}
				else
				{
					// 50% size
					if(!(x % 2) && !(y % 2))
					{
						bitmap.pix((y / 2 + m_bgscrolly) & 0x1ff, (x / 2 + m_bgscrollx) & 0x1ff) = 0x100 + color;

						u8 *const pri = &screen.priority().pix((y / 2 + m_bgscrolly) & 0x1ff);
						pri[(x / 2 + m_bgscrollx) & 0x1ff] |= 2;
					}
				}
			}

			count++;
		}
	}
}

u32 playmark_state::screen_update_bigtwin(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	screen.priority().fill(0, cliprect);

	m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	if (m_bg_enable)
		draw_bitmap(screen, bitmap, cliprect);
	draw_sprites(screen, bitmap, cliprect, 4);
	m_tx_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	return 0;
}


u32 playmark_state::screen_update_bigtwinb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	// video enabled
	if (m_scroll[6] & 1)
	{
		m_bg_tilemap->draw(screen, bitmap, cliprect, 0, 0);
		m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 0);
		bigtwinb_draw_sprites(screen, bitmap, cliprect, 4);
		m_tx_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	}
	else
		bitmap.fill(m_palette->black_pen(), cliprect);
	return 0;
}

u32 playmark_state::screen_update_excelsr(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	screen.priority().fill(0, cliprect);

	m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 1);
	if (m_bg_enable)
		draw_bitmap(screen, bitmap, cliprect);
	m_tx_tilemap->draw(screen, bitmap, cliprect, 0, 4);
	draw_sprites(screen, bitmap, cliprect, 2);
	return 0;
}

u32 playmark_state::screen_update_wbeachvl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	if (m_fg_rowscroll_enable)
	{
		int i;

		m_fg_tilemap->set_scroll_rows(512);
		for (i = 0; i < 256; i++)
			m_fg_tilemap->set_scrollx(i + 1, m_rowscroll[8 * i]);
	}
	else
	{
		m_fg_tilemap->set_scroll_rows(1);
		m_fg_tilemap->set_scrollx(0, m_fgscrollx);
	}

	screen.priority().fill(0, cliprect);

	m_bg_tilemap->draw(screen, bitmap, cliprect, 0, 1);
	m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 2);
	draw_sprites(screen, bitmap, cliprect, 0);
	m_tx_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	return 0;
}

u32 playmark_state::screen_update_hrdtimes(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	screen.priority().fill(0, cliprect);

	// video enabled
	if (m_scroll[6] & 1)
	{
		m_bg_tilemap->draw(screen, bitmap, cliprect, 0, 1);
		m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 2);
		draw_sprites(screen, bitmap, cliprect, 2);
		m_tx_tilemap->draw(screen, bitmap, cliprect, 0, 0);
	}
	else
		bitmap.fill(m_palette->black_pen(), cliprect);
	return 0;
}
