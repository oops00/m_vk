/*

	About: Vk include v2.2
	Author: PawnoCoder

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before m_vk"
#endif

#if !defined HTTP_ERROR_MALFORMED_RESPONSE
	#error "You must have a_http include in order to use this one."
#endif

#if defined _m_vk_included_
	#endinput
#endif
#define _m_vk_included_

/*
	Define const
*/

#if !defined M_VK_URL
	#error Please define the URL of the vk script. Example: #define M_VK_URL "example.com/m_vk.php"
#endif

#if !defined M_VK_TOKEN
	#error Please define Vk token to send messages. Example: #define M_VK_TOKEN "a4a15d548494c1c5daea9812484ef2141ed649657faad41141e9d97d4b11c6cc4eb969aac5ec4d747951e"
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if !defined MAX_PLAYER_VK
	#define MAX_PLAYER_VK 64
#endif

#if !defined MAX_VK_SIZE
	#define MAX_VK_SIZE 512
#endif

/*
	Natives
*/

native __m_vk__HTTP(index, type, const url[], const data[], const callback[]) = HTTP;

/*
	Define functions
*/

#define Vk_Create:%0(%1) \
	forward VC_%0(%1); \
	public VC_%0(%1)

#define Vk_Show::%0(%1) \
	VC_%0(%1)

#define Vk_Response:%0(%1) \
	forward VR_%0(%1); \
	public VR_%0(%1)

#define Vk: #

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

/*
	Forwards
*/

forward OnPlayerVkScriptResponse(playerid, response_code, const data[]);

/*
	Vars
*/

static
	v_player_function[MAX_PLAYERS][MAX_FUNCTION_NAME + 1 char];

/*
	Vk_Send
*/

stock Vk_Send(playerid, const function[], const domain[], const message[])
{
	new
		info[MAX_VK_SIZE + 1];

	v_player_function[playerid] = !"VR_";
	strcat(v_player_function[playerid], function);
	format(info, sizeof(info), "domain=%s&message=%s&access_token="M_VK_TOKEN"", domain, message);
	__m_vk__HTTP(playerid, HTTP_POST, M_VK_URL, info, !"OnPlayerVkScriptResponse");
	return 1;
}

/*
	OnPlayerVkScriptResponse
*/

public OnPlayerVkScriptResponse(playerid, response_code, const data[])
{
	if (funcidx(v_player_function[playerid]) != -1)
		CallLocalFunction(v_player_function[playerid], !"iis", playerid, response_code, (isnull(data)) ? (!"\1") : (data));
	return 1;
}