/*
 * Copyright (C) 2018, Ing.-Buero Dr. Michael Lehning, Hildesheim
 * Copyright (C) 2018, SICK AG, Waldkirch
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Osnabrück University nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *  Created on: 28th May 2018
 *
 *      Authors:
 *       Michael Lehning <michael.lehning@lehning.de>
 *
 */

#ifndef SICK_GENERIC_RADAR_H_
#define SICK_GENERIC_RADAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/String.h>

#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>
#include <sick_scan/sick_scan_common_nw.h>


#ifndef _MSC_VER
#include <dynamic_reconfigure/server.h>
#include <sick_scan/SickScanConfig.h>
#endif
#include "sick_scan/sick_generic_parser.h"
#include "sick_scan/sick_scan_common_nw.h"

namespace sick_scan
{

	class SickScanRadarRawTarget
	{
	public:
		float Dist() const { return dist; }
		void Dist(float val) { dist = val; }
		float Azimuth() const { return azimuth; }
		void Azimuth(float val) { azimuth = val; }
		float Vrad() const { return vrad; }
		void Vrad(float val) { vrad = val; }
		float Ampl() const { return ampl; }
		void Ampl(float val) { ampl = val; }
		int Mode() const { return mode; }
		void Mode(int val) { mode = val; }
	private:
		float dist;
		float azimuth;
		float vrad;
		float ampl;
		int mode;
	};

	class SickScanRadarObject
	{
	public:
		float P3Dx() const { return p3Dx; }
		void P3Dx(float val) { p3Dx = val; }
		float P3Dy() const { return p3Dy; }
		void P3Dy(float val) { p3Dy = val; }
		float V3Dx() const { return v3Dx; }
		void V3Dx(float val) { v3Dx = val; }
		float V3Dy() const { return v3Dy; }
		void V3Dy(float val) { v3Dy = val; }
		float ObjLength() const { return objLength; }
		void ObjLength(float val) { objLength = val; }

		int ObjId() const { return objId; }
		void ObjId(int val) { objId = val; }
	private:
		float p3Dx;
		float p3Dy;
		float v3Dx;
		float v3Dy;
		float objLength;
		int objId;
	};


	class SickScanRadar
	{
	public:
		SickScanRadar(SickScanCommon *commonPtr_)
		{
			commonPtr = commonPtr_;
		}
		int parseDatagram(unsigned char *receiveBuffer, int actual_length, bool useBinaryProtocol);	
		int parseAsciiDatagram(char* datagram, size_t datagram_length, std::vector<SickScanRadarObject> &objectList, std::vector<SickScanRadarRawTarget> &rawTargetList); /* , SickScanConfig &config, */ // sensor_msgs::LaserScan &msg, int &numEchos, int &echoMask);
		void simulateAsciiDatagram(unsigned char * receiveBuffer, int* actual_length);
	private:
		SickScanCommon *commonPtr;
		void simulateAsciiDatagramFromFile(unsigned char * receiveBuffer, int* actual_length);
	};

} /* namespace sick_scan */
#endif // SICK_GENERIC_RADAR_H_