package org.mqttserver.services.HTTP;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import org.mqttserver.services.MQTT.Broker;

public class DataService extends AbstractVerticle {

    private final int port;
    private final Broker broker;

    public DataService(int port, Broker broker) {
        this.port = port;
        this.broker = broker;
    }

    @Override
    public void start() {
        Router router = Router.router(vertx);
        router.route().handler(BodyHandler.create());
        router.post("/api/postdata").handler(this::handleAddNewData);
        router.get("/api/systemdata").handler(this::handleGetData);
        vertx.createHttpServer().requestHandler(router).listen(port);
        System.out.println("Service ready on port: " + port);
    }

    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        JsonObject res = routingContext.getBodyAsJson();
        if (res == null) {
            sendError(400, response);
        } else {
            try {
                int valveValue = res.getInteger("valveValue");
                broker.getSystemController().setValveValueFromDashboard(valveValue);
                broker.getSystemController().setIsManual(true);
                System.out.println("[OPERATOR] Valve Value set manually");
            } catch (Exception ex) {
                ex.printStackTrace();
            }

            try {
                boolean isManual = res.getBoolean("isManual");
                broker.getSystemController().setIsManual(isManual);
                if (!isManual) {
                    broker.getSystemController().setValveValueFromDashboard(-1);
                }
            } catch (Exception ex) {

            }
            response.setStatusCode(200).end();
        }
    }

    private void handleGetData(RoutingContext routingContext) {
        JsonArray arr = new JsonArray();
        JsonObject data = new JsonObject();
        data.put("status", broker.getSystemController().getStatus());
        data.put("valveValue", broker.getSystemController().getValveValue());
        data.put("wl", broker.getSystemController().getWl());
        arr.add(data);
        routingContext.response()
                .putHeader("content-type", "application/json")
                .end(arr.encodePrettily());
    }

    private void sendError(int statusCode, HttpServerResponse response) {
        response.setStatusCode(statusCode).end();
    }


}