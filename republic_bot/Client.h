#pragma once

#include "include\json.hpp"
#include "Database.h"

#include <algorithm>
#include <ctime>
#include <functional>
#include <ostream>
#include <sleepy_discord\websocketpp_websocket.h>
#include <unordered_map>
#include <vector>

using namespace SleepyDiscord;

/*
Function:		Client <class>
Parameters:		string <the bot token>, int <amount of threads to use>
Return Value:	this <its self>
Description:	Subclass of the Discord API being used.
*/
class Client : public DiscordClient {
private:
	Database * db_;
	std::string toggleFailed_ = "Please use as !toggle <faction/elo>.";
	std::string toggleSuccess_ = "Toggled %s to %s.";
	std::string showBalanceString_ = "Your ELO balance is: %d ELO";
	std::string showFactionString_ = "Your current Faction is: %s";
	std::string showFactionChangeString_ = "You changed faction to %s.";
	std::string showNoFactionString_ = "You have no current Faction.";
	std::string showFalseFactionString_ = "Sorry, the faction you chose does not exist.";
	std::string giveEloString_ = "You have given %d ELO to "; // The targets are added to the end of the string.
	std::string giveEloArgFailedString_ = "Please supply atleast 1 person and an amount.";
	std::string takeEloString_ = "You have taken %d ELO from "; // The targets are added to the end of the string.
	std::string takeEloArgFailedString_ = "Please supply atleast 1 person and an amount.";
	std::string muteUserString_ = "You have muted ";
	std::string muteUserFailedString_ = "You must supply a user/users to mute along with a time.";
	std::string unmuteUserString_ = "You have unmuted ";
	std::string unmuteUserFailedString_ = "You must supply a user/users to unmute.";
	std::string isUserMutedString_ = "Is user (%s) currently muted? %s.";
	std::vector<std::string> allFactions = {
		"Bandle_City",
		"Bilgewater",
		"Darkin",
		"Demacia",
		"Freljord",
		"Ionia",
		"Noxus",
		"Piltover",
		"Shadow_Isles",
		"Shurima",
		"Targon",
		"Void",
		"Zaun"
	};
	std::unordered_map<std::string, std::function<void(Client *, SleepyDiscord::Message, std::vector<std::string>)>> commandMap;

	bool commandBalanceEnabled = true;
	bool commandFactionEnabled = true;

public:
	// Used to initialise the DiscordClient before overloading methods.
	using DiscordClient::DiscordClient;

	/*
	Function:		Client::Client
	Parameters:		string <the discord bot token>, int <threads to be used>, Database <
	Return Value:	this <its self>
	Description:	Constructor overloading default to add database features.
	*/
	Client(std::string token, int threads, std::string dbLoc);

	/*
	Function:		Client::onMessage
	Parameters:		SleepyDiscord::Message <message context>
	Return Value:	None
	Description:	Event called upon a message being created.
	*/
	void onMessage(Message message);

	/*
	Function:		Client::addUserIfNotExists
	Parameters:		SleepyDiscord::User <the user to check>
	Return Value:	None
	Description:	Try to add the user to the database if needed.
	*/
	void addUserIfNotExists(User user);

	/*
	Function:		Client::handleToggle
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Handle the toggle command.
	*/
	void handleToggle(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::handleFaction
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Handle the faction command.
	*/
	void handleFaction(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::handleMute
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Handle the mute command.
	*/
	void handleMute(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::handleUnmute
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Handle the unmute command.
	*/
	void handleUnmute(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::handleIsMuted
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Handle the isMute command.
	*/
	void handleIsMuted(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::displayFaction
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Show the requesters faction.
	*/
	void displayFaction(Message message);

	/*
	Function:		Client::changeFaction
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Changes the requesters faction.
	*/
	void changeFaction(Message message, std::string faction);

	/*
	Function:		Client::displayBalance
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Show the requesters ELO balance.
	*/
	void displayBalance(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::giveElo
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Give the users mentioned the amount of ELO.
	*/
	void giveElo(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::takeElo
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Takes the users mentioned the amount of ELO.
	*/
	void takeElo(Message message, std::vector<std::string> tokens);

	/*
	Function:		Client::muteUser
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Mutes the indicated user for a period of time.
	*/
	void muteUser(User user, int time);

	/*
	Function:		Client::unmuteUser
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	None
	Description:	Unmutes the indicated user.
	*/
	void unmuteUser(User user);

	/*
	Function:		Client::isMuted
	Parameters:		SleepyDiscord::Message <the message to check>
	Return Value:	bool <is the user muted?>
	Description:	Checks if the user is muted.
	*/
	bool isMuted(User user);
};