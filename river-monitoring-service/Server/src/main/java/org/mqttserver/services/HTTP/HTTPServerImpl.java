package org.mqttserver.services.HTTP;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.MultiMap;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import org.mqttserver.services.MQTT.Broker;

public class HTTPServerImpl extends AbstractVerticle {

    @Override
    public void start() throws Exception {
        // Create a Router
        Router router = Router.router(vertx);
        // Create the HTTP server
        vertx.createHttpServer()
                // Handle every request using the router
                .requestHandler(router)
                // Start listening
                .listen(8050)
                // Print the port
                .onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()));
    }

}
