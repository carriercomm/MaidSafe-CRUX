///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 MaidSafe.net Limited
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MAIDSAFE_CRUX_DETAIL_RECEIVE_INPUT_TYPE_HPP
#define MAIDSAFE_CRUX_DETAIL_RECEIVE_INPUT_TYPE_HPP

#include <functional>
#include <boost/asio/buffer.hpp>
#include <boost/system/system_error.hpp>
#include <maidsafe/crux/detail/buffer.hpp>

namespace maidsafe { namespace crux { namespace detail {

struct receive_input_type
{
    using read_handler_type
        = std::function<void (const boost::system::error_code&, std::size_t)>;

    read_handler_type                        handler;
    std::vector<boost::asio::mutable_buffer> buffers;

    template<class MutableBufferSequence>
    receive_input_type( const MutableBufferSequence& payload_buffers
                      , read_handler_type&&          handler);
};

}}} // namespace maidsafe::crux::detail

namespace maidsafe { namespace crux { namespace detail {

template<class MutableBufferSequence>
receive_input_type::receive_input_type( const MutableBufferSequence& payload_buffers
                                      , read_handler_type&& handler)
    : handler(std::move(handler))
    , buffers(boost::asio::buffer_size(payload_buffers))
{
    std::size_t i = 0;
    for (const auto& buffer : payload_buffers) {
        this->buffers[i++] = buffer;
    }
}

}}} // namespace maidsafe::crux::detail

#endif // ifndef MAIDSAFE_CRUX_DETAIL_RECEIVE_INPUT_TYPE_HPP

