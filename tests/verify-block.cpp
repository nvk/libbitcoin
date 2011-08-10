#include <bitcoin/storage/postgresql_storage.hpp>
#include <bitcoin/util/logger.hpp>
#include <bitcoin/messages.hpp>
#include <bitcoin/verify.hpp>
#include <iostream>

using std::shared_ptr;
using libbitcoin::postgresql_storage;
typedef shared_ptr<postgresql_storage> psql_ptr;
using libbitcoin::verify_block;
typedef shared_ptr<verify_block> verify_block_ptr;

using std::placeholders::_1;
using std::placeholders::_2;

void block_status(std::error_code ec, bool is_good)
{
    if (ec)
        libbitcoin::log_error() << "Verifying block: " << ec.message() << "\n";
    std::cout << "block is " << (is_good ? "good" : "bad") << "\n";
}

void recv_block(std::error_code ec, libbitcoin::message::block block, verify_block_ptr verif)
{
    if (ec)
    {
        std::cerr << ec.message() << "\n";
        return;
    }
    verif->start(block, block_status);
}

int main()
{
    psql_ptr psql(new postgresql_storage("bitcoin", "genjix"));
    verify_block_ptr verif(new verify_block(psql));
    psql->fetch_block_by_depth(2, std::bind(recv_block, _1, _2, verif));
    std::cin.get();
    return 0;
}

