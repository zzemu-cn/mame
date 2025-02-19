// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Pierpaolo Prazzoli, Quench
#ifndef MAME_INCLUDES_PLAYMARK_H
#define MAME_INCLUDES_PLAYMARK_H

#pragma once

#include "sound/okim6295.h"
#include "machine/eepromser.h"
#include "machine/ticket.h"
#include "cpu/pic16c5x/pic16c5x.h"
#include "emupal.h"
#include "tilemap.h"

class playmark_state : public driver_device
{
public:
	playmark_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_bgvideoram(*this, "bgvideoram"),
		m_videoram(*this, "videoram%u", 1U),
		m_spriteram(*this, "spriteram"),
		m_rowscroll(*this, "rowscroll"),
		m_sprtranspen(0),
		m_oki(*this, "oki"),
		m_okibank(*this, "okibank"),
		m_eeprom(*this, "eeprom"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette"),
		m_ticket(*this, "ticket"),
		m_token(*this, "token")
	{ }

	void wbeachvl(machine_config &config);
	void hrdtimes(machine_config &config);
	void luckboomh(machine_config &config);
	void bigtwin(machine_config &config);
	void hotmind(machine_config &config);
	void bigtwinb(machine_config &config);
	void excelsr(machine_config &config);

	void init_pic_decode();

protected:
	virtual void machine_start() override;
	virtual void machine_reset() override;

	// memory pointers
	optional_shared_ptr<u16> m_bgvideoram;
	optional_shared_ptr_array<u16, 3> m_videoram;
	required_shared_ptr<u16> m_spriteram;
	optional_shared_ptr<u16> m_rowscroll;

	// video-related
	tilemap_t *m_tx_tilemap;
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	s32 m_bgscrollx;
	s16 m_bgscrolly;
	bool m_bg_enable;
	bool m_bg_full_size;
	u32 m_fgscrollx;
	bool m_fg_rowscroll_enable;

	s8 m_xoffset;
	s8 m_yoffset;
	u16 m_pri_masks[3];
	u16 m_scroll[7];
	u8 m_sprtranspen;

	// misc
	u16 m_snd_command;
	u16 m_snd_flag;
	u8 m_oki_control;
	u8 m_oki_command;
	u8 m_dispenser_latch;
	u8 m_oki_numbanks;
	void configure_oki_banks();

	// devices
	required_device<okim6295_device> m_oki;
	optional_memory_bank m_okibank;
	optional_device<eeprom_serial_93cxx_device> m_eeprom;
	required_device<cpu_device> m_maincpu;
	optional_device<pic16c57_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;
	optional_device<ticket_dispenser_device> m_ticket;
	optional_device<ticket_dispenser_device> m_token;

private:
	void coinctrl_w(u8 data);
	void wbeachvl_coin_eeprom_w(u8 data);
	void hotmind_coin_eeprom_w(u8 data);
	void luckboomh_dispenser_w(u8 data);
	void playmark_snd_command_w(u8 data);
	u8 playmark_snd_command_r();
	u8 playmark_snd_flag_r();
	void playmark_oki_w(u8 data);
	void playmark_snd_control_w(u8 data);
	void hrdtimes_snd_control_w(u8 data);
	void wbeachvl_txvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void wbeachvl_fgvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void wbeachvl_bgvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void hrdtimes_txvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void hrdtimes_fgvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void hrdtimes_bgvideoram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void bigtwin_scroll_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void wbeachvl_scroll_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void excelsr_scroll_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void hrdtimes_scroll_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void playmark_oki_banking_w(u8 data);
	TILE_GET_INFO_MEMBER(bigtwin_get_tx_tile_info);
	TILE_GET_INFO_MEMBER(bigtwin_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(wbeachvl_get_tx_tile_info);
	TILE_GET_INFO_MEMBER(wbeachvl_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(wbeachvl_get_bg_tile_info);
	TILE_GET_INFO_MEMBER(hrdtimes_get_tx_tile_info);
	TILE_GET_INFO_MEMBER(bigtwinb_get_tx_tile_info);
	TILE_GET_INFO_MEMBER(hrdtimes_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(hrdtimes_get_bg_tile_info);
	DECLARE_VIDEO_START(bigtwin);
	DECLARE_VIDEO_START(bigtwinb);
	DECLARE_VIDEO_START(wbeachvl);
	DECLARE_VIDEO_START(excelsr);
	DECLARE_VIDEO_START(hotmind);
	DECLARE_VIDEO_START(hrdtimes);
	DECLARE_VIDEO_START(luckboomh);
	TILEMAP_MAPPER_MEMBER(playmark_tilemap_scan_pages);
	u32 screen_update_bigtwin(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_bigtwinb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_wbeachvl(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_excelsr(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_hrdtimes(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int codeshift );
	void bigtwinb_draw_sprites( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect, int codeshift );
	void draw_bitmap( screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect );
	u8 playmark_asciitohex(u8 data);
	void playmark_decode_pic_hex_dump(void);

	void bigtwin_main_map(address_map &map);
	void bigtwinb_main_map(address_map &map);
	void excelsr_main_map(address_map &map);
	void hotmind_main_map(address_map &map);
	void hrdtimes_main_map(address_map &map);
	void luckboomh_main_map(address_map &map);
	void oki_map(address_map &map);
	void wbeachvl_main_map(address_map &map);
};

#endif // MAME_INCLUDES_PLAYMARK_H
