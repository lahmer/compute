//
// Created by lahmer on 8/16/16.
//

#include "ResquestServer.h"

boost::asio::io_service* ResquestServer::m_ios;
boost::asio::ip::tcp::acceptor* ResquestServer::m_acceptor;
boost::asio::ssl::context* ResquestServer::m_ctx;

void ResquestServer::InitResquestServer() {
    m_ios = new boost::asio::io_service();
    m_acceptor = new boost::asio::ip::tcp::acceptor(*m_ios,
    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),Compute::g_RequestServerPortNumber));
    m_ctx = new boost::asio::ssl::context(*m_ios,boost::asio::ssl::context::sslv23);

    //Setting the ssl context
    m_ctx->set_options(boost::asio::ssl::context::default_workarounds
    | boost::asio::ssl::context::no_sslv2
    | boost::asio::ssl::context::single_dh_use);
    //Setting ths password callback
    m_ctx->set_password_callback([](std::size_t max_length,
    boost::asio::ssl::context::password_purpose purpose) -> std::string {
        return Compute::g_RequestServerCallbackPassword;
    });
    //Setting the certificate files
    m_ctx->use_certificate_chain_file(Compute::g_RequestServerCertificateFilePath.c_str());
    m_ctx->use_private_key_file(Compute::g_RequestServerKeyFilePath , boost::asio::ssl::context::pem);
    m_ctx->use_tmp_dh_file(Compute::g_TmpDhFilePath);
    m_acceptor->listen();
//launching the connection manager
    ConnectionManager::InitialiseConnectionManager();




  /*  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_stream(*m_ios,*m_ctx);
    m_acceptor->accept(ssl_stream.lowest_layer());
    ssl_stream.handshake(boost::asio::ssl::stream_base::server);

    boost::asio::streambuf request;
    boost::asio::read_until(ssl_stream,request,'\n');

    std::string response = "response \n";
    boost::asio::write(ssl_stream,boost::asio::buffer(response));*/

    //while(true);
}