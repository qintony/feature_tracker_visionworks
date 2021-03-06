/*
# Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __NVX_FEATURE_TRACKER_HPP__
#define __NVX_FEATURE_TRACKER_HPP__

#include <VX/vx.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

namespace nvx
{
    class FeatureTracker
    {
    public:
        struct HarrisPyrLKParams
        {
            // parameters for optical flow node
            vx_uint32 pyr_levels;
            vx_uint32 lk_num_iters;
            vx_uint32 lk_win_size;

            // parameters for harris_track node
            vx_float32 harris_k;
            vx_float32 harris_thresh;
            vx_uint32 harris_cell_size;
            vx_uint32 array_capacity;

            HarrisPyrLKParams();
        };

        static FeatureTracker* createHarrisPyrLK(vx_context context, const HarrisPyrLKParams& params = HarrisPyrLKParams());

        virtual ~FeatureTracker() {}

        virtual void init(vx_image firstFrame, vx_image mask = 0) = 0;
        virtual void track(vx_image newFrame, vx_image mask = 0) = 0;

        // get list of tracked features on previous frame
        virtual vx_array getPrevFeatures() const = 0;

        // get list of tracked features on current frame
        virtual vx_array getCurrFeatures() const = 0;
        virtual vx_array getOpticalFeatures() const = 0;
        virtual vx_array getHarrisFeatures() const = 0;
        virtual vx_array getOptIn() const = 0;
        virtual void optIn(std::vector<cv::Point2f> &v ){ std::cout<<"cao"<<std::endl;} ;

        virtual void printPerfs() const = 0;
    };
}

#endif
