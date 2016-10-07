
/*  brick.c was generated by yup.py (yupp) 1.0b1
    out of brick.yu-c 
 *//**
 *  \file  brick.c (brick.yu-c)
 *  \brief  Simplified interface of "ev3dev-c" library.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#define BRICK_IMPLEMENT

#include <string.h>
#include "brick.h"

/**
 *  \addtogroup brick
 *  \{
 */

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( ms ) usleep(( ms ) * 1000 )

//////////////////////////////////////////////////
#endif

POOL_T port_to_socket( uint8_t port )
{
	switch ( port ) {
	case INPUT_1:
		return IN1;
	case INPUT_2:
		return IN2;
	case INPUT_3:
		return IN3;
	case INPUT_4:
		return IN4;
	case OUTPUT_A:
		return OUTA;
	case OUTPUT_B:
		return OUTB;
	case OUTPUT_C:
		return OUTC;
	case OUTPUT_D:
		return OUTD;

	}
	return ( 0 );
}

uint8_t socket_to_port( POOL_T sock )
{
	switch ( sock ) {
	case IN1:
		return INPUT_1;
	case IN2:
		return INPUT_2;
	case IN3:
		return INPUT_3;
	case IN4:
		return INPUT_4;
	case OUTA:
		return OUTPUT_A;
	case OUTB:
		return OUTPUT_B;
	case OUTC:
		return OUTPUT_C;
	case OUTD:
		return OUTPUT_D;

	}
	return ( EV3_PORT__NONE_ );
}

bool brick_init( void )
{
	if ( ev3_init() < 1 ) return ( false );
	ev3_sensor_init();
	ev3_tacho_init();
	ev3_dc_init();
	return ( true );
}

void brick_uninit( void )
{
	ev3_uninit();
}

uint8_t brick_keys( void )
{
	uint8_t keys = 0;  /* default result */

	ev3_read_keys( &keys );
	return ( keys );
}

static bool sensor_pool_to_desc( POOL_T pool, uint8_t *sn )
{
	uint8_t _sn;

	memset( sn, DESC_LIMIT, DESC_VEC_LEN );
	for ( _sn = 0; _sn < DESC_LIMIT; _sn++ ) {
		if ( ev3_sensor[ _sn ].type_inx != SENSOR_TYPE__NONE_ ) {
			uint8_t sock = port_to_socket( ev3_sensor[ _sn ].port );
			if ( sock & pool ) {
				*sn = _sn;
				++sn;
				pool &= ~sock;
				if ( pool == 0 ) return ( true );
			}
		}
	}
	return ( false );
}

char *sensor_get_address( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_address( sn, buf, sz );
	}
	return ( buf );
}

byte *sensor_get_bin_data( POOL_T sock, byte *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_bin_data( sn, buf, sz );
	}
	return ( buf );
}

bool sensor_set_bin_data( POOL_T pool, byte *value, size_t sz )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_bin_data( sn, value, sz ) > 0 );
	}
	return ( false );
}

char *sensor_get_bin_data_format( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_bin_data_format( sn, buf, sz );
	}
	return ( buf );
}

bool sensor_set_command( POOL_T pool, INX_T command_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_command_inx( sn, command_inx ) > 0 );
	}
	return ( false );
}

char *sensor_get_commands( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_commands( sn, buf, sz );
	}
	return ( buf );
}

char *sensor_get_direct( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_direct( sn, buf, sz );
	}
	return ( buf );
}

bool sensor_set_direct( POOL_T pool, char *value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_direct( sn, value ) > 0 );
	}
	return ( false );
}

dword sensor_get_decimals( POOL_T sock, dword defval )
{
	uint8_t sn;
	dword val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_decimals( sn, buf );
	}
	return ( *buf );
}

char *sensor_get_driver_name( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_driver_name( sn, buf, sz );
	}
	return ( buf );
}

char *sensor_get_fw_version( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_fw_version( sn, buf, sz );
	}
	return ( buf );
}

INX_T sensor_get_mode( POOL_T sock )
{
	uint8_t sn;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		return ( get_sensor_mode_inx( sn ));
	}
	return ( SENSOR_MODE__UNKNOWN_ );
}

bool sensor_set_mode( POOL_T pool, INX_T mode_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_mode_inx( sn, mode_inx ) > 0 );
	}
	return ( false );
}

char *sensor_get_modes( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_modes( sn, buf, sz );
	}
	return ( buf );
}

dword sensor_get_num_values( POOL_T sock, dword defval )
{
	uint8_t sn;
	dword val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_num_values( sn, buf );
	}
	return ( *buf );
}

dword sensor_get_poll_ms( POOL_T sock, dword defval )
{
	uint8_t sn;
	dword val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_poll_ms( sn, buf );
	}
	return ( *buf );
}

bool sensor_set_poll_ms( POOL_T pool, dword value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( sensor_pool_to_desc( pool, sn )) {
		return ( multi_set_sensor_poll_ms( sn, value ) > 0 );
	}
	return ( false );
}

char *sensor_get_units( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_units( sn, buf, sz );
	}
	return ( buf );
}

float sensor_get_value0( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value0( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value1( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value1( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value2( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value2( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value3( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value3( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value4( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value4( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value5( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value5( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value6( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value6( sn, buf );
	}
	return ( *buf );
}

float sensor_get_value7( POOL_T sock, float defval )
{
	uint8_t sn;
	float val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value7( sn, buf );
	}
	return ( *buf );
}

char *sensor_get_text_value( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_text_value( sn, buf, sz );
	}
	return ( buf );
}

int sensor_get_value( uint8_t inx, POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_sensor_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_sensor_value( inx, sn, buf );
	}
	return ( *buf );
}

bool us_set_mode_us_dist_cm( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_DIST_CM );
}

bool us_set_mode_us_dist_in( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_DIST_IN );
}

bool us_set_mode_us_listen( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_LISTEN );
}

bool us_set_mode_us_si_cm( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_SI_CM );
}

bool us_set_mode_us_si_in( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_SI_IN );
}

bool us_set_mode_us_dc_cm( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_DC_CM );
}

bool us_set_mode_us_dc_in( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_US_US_DC_IN );
}
					
bool gyro_set_mode_gyro_ang( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_GYRO_GYRO_ANG );
}

bool gyro_set_mode_gyro_rate( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_GYRO_GYRO_RATE );
}

bool gyro_set_mode_gyro_fas( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_GYRO_GYRO_FAS );
}

bool gyro_set_mode_gyro_g_and_a( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_GYRO_GYRO_G_AND_A );
}

bool gyro_set_mode_gyro_cal( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_GYRO_GYRO_CAL );
}
					
bool color_set_mode_col_reflect( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_COL_REFLECT );
}

bool color_set_mode_col_ambient( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_COL_AMBIENT );
}

bool color_set_mode_col_color( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_COL_COLOR );
}

bool color_set_mode_ref_raw( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_REF_RAW );
}

bool color_set_mode_rgb_raw( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_RGB_RAW );
}

bool color_set_mode_col_cal( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_COLOR_COL_CAL );
}
					
bool touch_set_mode_touch( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_TOUCH_TOUCH );
}
					
bool ir_set_mode_ir_prox( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_PROX );
}

bool ir_set_mode_ir_seek( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_SEEK );
}

bool ir_set_mode_ir_remote( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_REMOTE );
}

bool ir_set_mode_ir_rem_a( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_REM_A );
}

bool ir_set_mode_ir_s_alt( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_S_ALT );
}

bool ir_set_mode_ir_cal( POOL_T pool )
{
	return sensor_set_mode( pool, LEGO_EV3_IR_IR_CAL );
}
																																									
POOL_T sensor_search( INX_T type_inx )
{
	uint8_t sn = 0;
	POOL_T pool = SOCKET__NONE_;

	while ( ev3_search_sensor( type_inx, &sn, sn )) {
		pool |= port_to_socket( ev3_sensor[ sn++ ].port );
	}
	return ( pool );
}

bool sensor_is_plugged( POOL_T pool, INX_T type_inx )
{
	uint8_t sn;

	if ( pool == SOCKET__NONE_ ) return ( false );

	if ( OUTA & pool ) {
		if ( !ev3_search_sensor_plugged_in( socket_to_port( OUTA ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != SENSOR_TYPE__NONE_ ) && ( ev3_sensor[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTB & pool ) {
		if ( !ev3_search_sensor_plugged_in( socket_to_port( OUTB ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != SENSOR_TYPE__NONE_ ) && ( ev3_sensor[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTC & pool ) {
		if ( !ev3_search_sensor_plugged_in( socket_to_port( OUTC ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != SENSOR_TYPE__NONE_ ) && ( ev3_sensor[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTD & pool ) {
		if ( !ev3_search_sensor_plugged_in( socket_to_port( OUTD ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != SENSOR_TYPE__NONE_ ) && ( ev3_sensor[ sn ].type_inx != type_inx )) return ( false );
	}

	return ( true );
}

static bool tacho_pool_to_desc( POOL_T pool, uint8_t *sn )
{
	uint8_t _sn;

	memset( sn, DESC_LIMIT, DESC_VEC_LEN );
	for ( _sn = 0; _sn < DESC_LIMIT; _sn++ ) {
		if ( ev3_tacho[ _sn ].type_inx != TACHO_TYPE__NONE_ ) {
			uint8_t sock = port_to_socket( ev3_tacho[ _sn ].port );
			if ( sock & pool ) {
				*sn = _sn;
				++sn;
				pool &= ~sock;
				if ( pool == 0 ) return ( true );
			}
		}
	}
	return ( false );
}

char *tacho_get_address( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_address( sn, buf, sz );
	}
	return ( buf );
}

bool tacho_set_command( POOL_T pool, INX_T command_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_command_inx( sn, command_inx ) > 0 );
	}
	return ( false );
}

char *tacho_get_commands( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_commands( sn, buf, sz );
	}
	return ( buf );
}

int tacho_get_count_per_rot( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_count_per_rot( sn, buf );
	}
	return ( *buf );
}

int tacho_get_count_per_m( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_count_per_m( sn, buf );
	}
	return ( *buf );
}

int tacho_get_full_travel_count( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_full_travel_count( sn, buf );
	}
	return ( *buf );
}

char *tacho_get_driver_name( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_driver_name( sn, buf, sz );
	}
	return ( buf );
}

int tacho_get_duty_cycle( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_duty_cycle( sn, buf );
	}
	return ( *buf );
}

int tacho_get_duty_cycle_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_duty_cycle_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_duty_cycle_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_duty_cycle_sp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_hold_pid_Kd( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_hold_pid_Kd( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_hold_pid_Kd( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_hold_pid_Kd( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_hold_pid_Ki( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_hold_pid_Ki( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_hold_pid_Ki( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_hold_pid_Ki( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_hold_pid_Kp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_hold_pid_Kp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_hold_pid_Kp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_hold_pid_Kp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_max_speed( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_max_speed( sn, buf );
	}
	return ( *buf );
}

INX_T tacho_get_polarity( POOL_T sock )
{
	uint8_t sn;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		return ( get_tacho_polarity_inx( sn ));
	}
	return ( TACHO_POLARITY__UNKNOWN_ );
}

bool tacho_set_polarity( POOL_T pool, INX_T polarity_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_polarity_inx( sn, polarity_inx ) > 0 );
	}
	return ( false );
}

int tacho_get_position( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_position( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_position( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_position( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_position_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_position_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_position_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_position_sp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_ramp_down_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_ramp_down_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_ramp_down_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_ramp_down_sp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_ramp_up_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_ramp_up_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_ramp_up_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_ramp_up_sp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_speed( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_speed( sn, buf );
	}
	return ( *buf );
}

int tacho_get_speed_pid_Kd( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_speed_pid_Kd( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_speed_pid_Kd( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_speed_pid_Kd( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_speed_pid_Ki( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_speed_pid_Ki( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_speed_pid_Ki( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_speed_pid_Ki( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_speed_pid_Kp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_speed_pid_Kp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_speed_pid_Kp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_speed_pid_Kp( sn, value ) > 0 );
	}
	return ( false );
}

int tacho_get_speed_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_speed_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_speed_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_speed_sp( sn, value ) > 0 );
	}
	return ( false );
}

FLAGS_T tacho_get_state( POOL_T sock )
{
	uint8_t sn;
	FLAGS_T flags = TACHO_STATE__NONE_;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_state_flags( sn, &flags );
	}
	return ( flags );
}

INX_T tacho_get_stop_action( POOL_T sock )
{
	uint8_t sn;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		return ( get_tacho_stop_action_inx( sn ));
	}
	return ( TACHO_STOP_ACTION__UNKNOWN_ );
}

bool tacho_set_stop_action( POOL_T pool, INX_T stop_action_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_stop_action_inx( sn, stop_action_inx ) > 0 );
	}
	return ( false );
}

char *tacho_get_stop_actions( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_stop_actions( sn, buf, sz );
	}
	return ( buf );
}

int tacho_get_time_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_tacho_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_tacho_time_sp( sn, buf );
	}
	return ( *buf );
}

bool tacho_set_time_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( tacho_pool_to_desc( pool, sn )) {
		return ( multi_set_tacho_time_sp( sn, value ) > 0 );
	}
	return ( false );
}

bool tacho_run_forever( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RUN_FOREVER );
}

bool tacho_run_to_abs_pos( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RUN_TO_ABS_POS );
}

bool tacho_run_to_rel_pos( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RUN_TO_REL_POS );
}

bool tacho_run_timed( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RUN_TIMED );
}

bool tacho_run_direct( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RUN_DIRECT );
}

bool tacho_stop( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_STOP );
}

bool tacho_reset( POOL_T pool )
{
	return tacho_set_command( pool, TACHO_RESET );
}
	
bool tacho_set_polarity_normal( POOL_T pool )
{
	return tacho_set_polarity( pool, TACHO_NORMAL );
}

bool tacho_set_polarity_inversed( POOL_T pool )
{
	return tacho_set_polarity( pool, TACHO_INVERSED );
}
	
bool tacho_set_stop_action_coast( POOL_T pool )
{
	return tacho_set_stop_action( pool, TACHO_COAST );
}

bool tacho_set_stop_action_brake( POOL_T pool )
{
	return tacho_set_stop_action( pool, TACHO_BRAKE );
}

bool tacho_set_stop_action_hold( POOL_T pool )
{
	return tacho_set_stop_action( pool, TACHO_HOLD );
}

POOL_T tacho_search( INX_T type_inx )
{
	uint8_t sn = 0;
	POOL_T pool = SOCKET__NONE_;

	while ( ev3_search_tacho( type_inx, &sn, sn )) {
		pool |= port_to_socket( ev3_tacho[ sn++ ].port );
	}
	return ( pool );
}

bool tacho_is_plugged( POOL_T pool, INX_T type_inx )
{
	uint8_t sn;

	if ( pool == SOCKET__NONE_ ) return ( false );

	if ( OUTA & pool ) {
		if ( !ev3_search_tacho_plugged_in( socket_to_port( OUTA ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != TACHO_TYPE__NONE_ ) && ( ev3_tacho[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTB & pool ) {
		if ( !ev3_search_tacho_plugged_in( socket_to_port( OUTB ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != TACHO_TYPE__NONE_ ) && ( ev3_tacho[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTC & pool ) {
		if ( !ev3_search_tacho_plugged_in( socket_to_port( OUTC ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != TACHO_TYPE__NONE_ ) && ( ev3_tacho[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTD & pool ) {
		if ( !ev3_search_tacho_plugged_in( socket_to_port( OUTD ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != TACHO_TYPE__NONE_ ) && ( ev3_tacho[ sn ].type_inx != type_inx )) return ( false );
	}

	return ( true );
}

bool tacho_is_running( POOL_T pool )
{
	if ( OUTA & pool ) {
		if ( tacho_get_state( OUTA ) != TACHO_STATE__NONE_ ) return ( true );
	}
	if ( OUTB & pool ) {
		if ( tacho_get_state( OUTB ) != TACHO_STATE__NONE_ ) return ( true );
	}
	if ( OUTC & pool ) {
		if ( tacho_get_state( OUTC ) != TACHO_STATE__NONE_ ) return ( true );
	}
	if ( OUTD & pool ) {
		if ( tacho_get_state( OUTD ) != TACHO_STATE__NONE_ ) return ( true );
	}

	return ( false );
}

static bool dc_pool_to_desc( POOL_T pool, uint8_t *sn )
{
	uint8_t _sn;

	memset( sn, DESC_LIMIT, DESC_VEC_LEN );
	for ( _sn = 0; _sn < DESC_LIMIT; _sn++ ) {
		if ( ev3_dc[ _sn ].type_inx != DC_TYPE__NONE_ ) {
			uint8_t sock = port_to_socket( ev3_dc[ _sn ].port );
			if ( sock & pool ) {
				*sn = _sn;
				++sn;
				pool &= ~sock;
				if ( pool == 0 ) return ( true );
			}
		}
	}
	return ( false );
}

char *dc_get_address( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_address( sn, buf, sz );
	}
	return ( buf );
}

bool dc_set_command( POOL_T pool, INX_T command_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_command_inx( sn, command_inx ) > 0 );
	}
	return ( false );
}

char *dc_get_commands( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_commands( sn, buf, sz );
	}
	return ( buf );
}

char *dc_get_driver_name( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_driver_name( sn, buf, sz );
	}
	return ( buf );
}

int dc_get_duty_cycle( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_duty_cycle( sn, buf );
	}
	return ( *buf );
}

int dc_get_duty_cycle_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_duty_cycle_sp( sn, buf );
	}
	return ( *buf );
}

bool dc_set_duty_cycle_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_duty_cycle_sp( sn, value ) > 0 );
	}
	return ( false );
}

INX_T dc_get_polarity( POOL_T sock )
{
	uint8_t sn;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		return ( get_dc_polarity_inx( sn ));
	}
	return ( DC_POLARITY__UNKNOWN_ );
}

bool dc_set_polarity( POOL_T pool, INX_T polarity_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_polarity_inx( sn, polarity_inx ) > 0 );
	}
	return ( false );
}

FLAGS_T dc_get_state( POOL_T sock )
{
	uint8_t sn;
	FLAGS_T flags = DC_STATE__NONE_;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_state_flags( sn, &flags );
	}
	return ( flags );
}

bool dc_set_stop_action( POOL_T pool, INX_T stop_action_inx )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_stop_action_inx( sn, stop_action_inx ) > 0 );
	}
	return ( false );
}

char *dc_get_stop_actions( POOL_T sock, char *buf, size_t sz )
{
	uint8_t sn;
				
	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_stop_actions( sn, buf, sz );
	}
	return ( buf );
}

int dc_get_ramp_down_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_ramp_down_sp( sn, buf );
	}
	return ( *buf );
}

bool dc_set_ramp_down_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_ramp_down_sp( sn, value ) > 0 );
	}
	return ( false );
}

int dc_get_ramp_up_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_ramp_up_sp( sn, buf );
	}
	return ( *buf );
}

bool dc_set_ramp_up_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_ramp_up_sp( sn, value ) > 0 );
	}
	return ( false );
}

int dc_get_time_sp( POOL_T sock, int defval )
{
	uint8_t sn;
	int val = defval, *buf = &val;

	if (( sock != SOCKET__NONE_ ) && ev3_search_dc_plugged_in( socket_to_port( sock ), EXT_PORT__NONE_, &sn, 0 )) {
		get_dc_time_sp( sn, buf );
	}
	return ( *buf );
}

bool dc_set_time_sp( POOL_T pool, int value )
{
	uint8_t sn[ DESC_VEC_LEN ];

	if ( dc_pool_to_desc( pool, sn )) {
		return ( multi_set_dc_time_sp( sn, value ) > 0 );
	}
	return ( false );
}

bool dc_run_forever( POOL_T pool )
{
	return dc_set_command( pool, DC_RUN_FOREVER );
}

bool dc_run_timed( POOL_T pool )
{
	return dc_set_command( pool, DC_RUN_TIMED );
}

bool dc_run_direct( POOL_T pool )
{
	return dc_set_command( pool, DC_RUN_DIRECT );
}

bool dc_stop( POOL_T pool )
{
	return dc_set_command( pool, DC_STOP );
}
	
bool dc_set_polarity_normal( POOL_T pool )
{
	return dc_set_polarity( pool, DC_NORMAL );
}

bool dc_set_polarity_inversed( POOL_T pool )
{
	return dc_set_polarity( pool, DC_INVERSED );
}
	
bool dc_set_stop_action_coast( POOL_T pool )
{
	return dc_set_stop_action( pool, DC_COAST );
}

bool dc_set_stop_action_brake( POOL_T pool )
{
	return dc_set_stop_action( pool, DC_BRAKE );
}

POOL_T dc_search( INX_T type_inx )
{
	uint8_t sn = 0;
	POOL_T pool = SOCKET__NONE_;

	while ( ev3_search_dc( type_inx, &sn, sn )) {
		pool |= port_to_socket( ev3_dc[ sn++ ].port );
	}
	return ( pool );
}

bool dc_is_plugged( POOL_T pool, INX_T type_inx )
{
	uint8_t sn;

	if ( pool == SOCKET__NONE_ ) return ( false );

	if ( OUTA & pool ) {
		if ( !ev3_search_dc_plugged_in( socket_to_port( OUTA ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != DC_TYPE__NONE_ ) && ( ev3_dc[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTB & pool ) {
		if ( !ev3_search_dc_plugged_in( socket_to_port( OUTB ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != DC_TYPE__NONE_ ) && ( ev3_dc[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTC & pool ) {
		if ( !ev3_search_dc_plugged_in( socket_to_port( OUTC ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != DC_TYPE__NONE_ ) && ( ev3_dc[ sn ].type_inx != type_inx )) return ( false );
	}
	if ( OUTD & pool ) {
		if ( !ev3_search_dc_plugged_in( socket_to_port( OUTD ), EXT_PORT__NONE_, &sn, 0 ) ) return ( false );
		if (( type_inx != DC_TYPE__NONE_ ) && ( ev3_dc[ sn ].type_inx != type_inx )) return ( false );
	}

	return ( true );
}

bool dc_is_running( POOL_T pool )
{
	if ( OUTA & pool ) {
		if ( dc_get_state( OUTA ) != DC_STATE__NONE_ ) return ( true );
	}
	if ( OUTB & pool ) {
		if ( dc_get_state( OUTB ) != DC_STATE__NONE_ ) return ( true );
	}
	if ( OUTC & pool ) {
		if ( dc_get_state( OUTC ) != DC_STATE__NONE_ ) return ( true );
	}
	if ( OUTD & pool ) {
		if ( dc_get_state( OUTD ) != DC_STATE__NONE_ ) return ( true );
	}

	return ( false );
}

void sleep_ms( uint32_t ms )
{
	Sleep( ms );
}

/** \} */
