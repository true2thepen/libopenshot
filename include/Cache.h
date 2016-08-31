/**
 * @file
 * @brief Header file for Cache class
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENSHOT_CACHE_H
#define OPENSHOT_CACHE_H

#include <map>
#include <deque>
#include <tr1/memory>
#include "CacheBase.h"
#include "Frame.h"
#include "Exceptions.h"

namespace openshot {

	/**
	 * @brief This class is a cache manager for Frame objects.
	 *
	 * It is used by FileReaders (such as FFmpegReader) to cache recently accessed frames. Due to the
	 * high cost of decoding streams, once a frame is decoded, converted to RGB, and a Frame object is created,
	 * it critical to keep these Frames cached for performance reasons.  However, the larger the cache, the more memory
	 * is required.  You can set the max number of bytes to cache.
	 */
	class Cache : public CacheBase {
	private:
		map<long int, tr1::shared_ptr<Frame> > frames;	///< This map holds the frame number and Frame objects
		deque<long int> frame_numbers;	///< This queue holds a sequential list of cached Frame numbers

		/// Clean up cached frames that exceed the max number of bytes
		void CleanUp();


	public:
		/// Default constructor, no max bytes
		Cache();

		/// @brief Constructor that sets the max bytes to cache
		/// @param max_bytes The maximum bytes to allow in the cache. Once exceeded, the cache will purge the oldest frames.
		Cache(int64 max_bytes);

		// Default destructor
		~Cache();

		/// @brief Add a Frame to the cache
		/// @param frame The openshot::Frame object needing to be cached.
		void Add(tr1::shared_ptr<Frame> frame);

		/// Clear the cache of all frames
		void Clear();

		/// Count the frames in the queue
		long int Count();

		/// @brief Get a frame from the cache
		/// @param frame_number The frame number of the cached frame
		tr1::shared_ptr<Frame> GetFrame(long int frame_number);

		/// Gets the maximum bytes value
		int64 GetBytes();

		/// Get the smallest frame number
		tr1::shared_ptr<Frame> GetSmallestFrame();

		/// @brief Move frame to front of queue (so it lasts longer)
		/// @param frame_number The frame number of the cached frame
		void MoveToFront(long int frame_number);

		/// @brief Remove a specific frame
		/// @param frame_number The frame number of the cached frame
		void Remove(long int frame_number);

	};

}

#endif
