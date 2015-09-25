/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_STEALTH_HPP
#define LIBBITCOIN_STEALTH_HPP

#include <cstdint>
#include <bitcoin/bitcoin/compat.hpp>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/chain/script.hpp>
#include <bitcoin/bitcoin/utility/binary.hpp>

namespace libbitcoin {
    
static BC_CONSTEXPR uint8_t ephemeral_public_key_sign = 0x02;

BC_API bool shared_secret(ec_secret& out_shared, const ec_secret& secret,
    const ec_compressed& point);

BC_API bool uncover_stealth(ec_compressed& out_stealth,
    const ec_compressed& ephemeral, const ec_secret& scan,
    const ec_compressed& spend);

BC_API bool uncover_stealth(ec_secret& out_stealth,
    const ec_compressed& ephemeral, const ec_secret& scan,
    const ec_secret& spend);

/// Convert a stealth info script to a prefix usable for stealth.
BC_API bool to_stealth_prefix(binary_type& out_prefix,
    const chain::script& script);

/// Extract the stealth ephemeral public key from an output script.
BC_API bool extract_ephemeral_key(ec_compressed& out_ephemeral_public_key,
    const chain::script& script);

/// Extract the unsigned stealth ephemeral public key from an output script.
BC_API bool extract_ephemeral_key(hash_digest& out_unsigned_ephemeral_key,
    const chain::script& script);

} // namespace libbitcoin

#endif
