#pragma once

#include "stdafx.h"

#include "Client.h"

#include <fstream>

// Json Configuration.
std::string		FILE_LOC_ = "config.json";
std::ifstream	FILE_DATA_;

/*
Function:		main
Parameters:		None
Return Value:	int <error code>
Description:	Initial entry point to the program.
*/
int main(void) {
	Client client("NDQxNjk5OTQxNDIxODA5NjY2.Dc6JRA.2TKJWxS_eFA9a1HE4Ng8Gu-uzcM", 2, ":memory:");
	client.run();
}
