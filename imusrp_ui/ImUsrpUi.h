#pragma once
#include "imgui.h"

#include <string>
#include <vector>
#include <iostream>
#include <thread>

// These are all USRP-related includes
#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/static.hpp>
#include <uhd/utils/thread.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>
//#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <csignal>
#include <fstream>

// Child windows
#include "ImUsrpUiRx.h"


class ImUsrpUi
{
public:
	ImUsrpUi();
	~ImUsrpUi();

	/// <summary>
	/// Primary render method. Called in the event loop.
	/// </summary>
	void render();

private:
	const char *m_windowname = "ImUSRP";

	/// <summary>
	/// Render section to display/refresh usrp pp_string.
	/// </summary>
	void render_usrp_info();
	std::string usrp_pp_string;

	/// <summary>
	/// Render section to display subdevice information.
	/// </summary>
	void render_subdev_info();
	uhd::usrp::subdev_spec_t tx_subdev_spec, rx_subdev_spec;

	/// <summary>
	/// Render section for receiver controls.
	/// </summary>
	void render_rx_options();
	void set_rx_options(size_t chnl);
	bool waiting_rx_settings = false;
	// Sample rate
	int rxrate = 1e6;
	double actualrxrate = 0; // actual is always double
	double rxratemin, rxratemax, rxratestep;
	// Frequencies
	float rxfreq = 1e9;
	double actualrxfreq = 0; // actual is always double
	double rxfreqmin, rxfreqmax, rxfreqstep;
	//// LO Offset (not sure how to get LO source name properly)
	//double rxlo_off = 0;
	//double actualrxlo_off;

	// Gain
	float rxgain = 0;
	double actualrxgain = 0; // actual is always double
	double rxgainmin, rxgainmax, rxgainstep;

	// Spare threads
	std::thread thd;
	bool thd_joined = true;

	// USRP object
	char device_addr_string[64];
	uhd::usrp::multi_usrp::sptr usrp;
	

	/// <summary>
	/// Method that wraps the usrp make() with a ready flag, for use in a separate thread.
	/// </summary>
	/// <param name="device_addr_string">Device address string</param>
	void usrp_make(std::string device_addr_string);
	bool usrp_ready = false;


	// Stream setups
	const char *wirefmts[2] = {"sc16", "sc8"};
	const char *cpufmts[4] = { "sc16", "sc8", "fc32", "fc64"};
	int wirefmtidx = 0;
	int cpufmtidx = 0;

	std::vector<ImUsrpUiRx> rxwindows;
};

