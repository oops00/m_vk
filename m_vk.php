<?php
	/*
	
		About: Vk include v2.2
		Author: PawnoCoder
		
	*/
	
	$domain = $_POST['domain'];
	$message = iconv("cp1251", "utf-8", $_POST['message']);
	$access_token = $_POST['access_token'];
	
	if (is_null($domain) || is_null($message) || is_null($access_token))
		die('Error: Missing parameters.');
	
	$curl = curl_init();
	
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_setopt($curl, CURLOPT_URL, 'https://api.vk.com/method/messages.send?domain=' . $domain . '&message=' . urlencode($message) . '&access_token=' . $access_token . '&v=5.57');
	
	$response = json_decode(curl_exec($curl))->{'response'};
	
	curl_setopt($curl, CURLOPT_URL, 'https://api.vk.com/method/messages.delete?message_ids=' . $response . '&access_token=' . $access_token . '&v=5.57');
	curl_exec($curl);
	curl_close($curl);
?>