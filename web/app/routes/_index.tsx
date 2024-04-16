import type { MetaFunction } from "@remix-run/node";
import { useEffect, useState } from "react";

export const meta: MetaFunction = () => {
  return [
    { title: "Physics Engine" },
    { name: "description", content: "Physics engine from scratch using SDL and C programming language" },
  ];
};

export default function Route() {
  const [socket, setSocket] = useState<WebSocket>();
  const [message, setMessage] = useState<string>("");

  useEffect(() => {
    const socket = new WebSocket('ws://localhost:7681', 'physics-engine');
    socket.onerror = (e) => {
      console.log(e);
    };
    socket.onclose = (e) => {
      setSocket(undefined);
    };

    socket.onmessage = (msg) => {
      setMessage(msg.data);
    };
    socket.onopen = (e) => {
      setSocket(socket);
    };
    return () => {
      socket?.close();
    };
  }, []);


  if (!socket) {
    return (
      <div>
        <span>Socket Disconnected</span>
      </div>
    );
  }

  return (
    <div style={{ fontFamily: "system-ui, sans-serif", lineHeight: "1.8" }}>
      <h1>Physics Engine</h1>
      <h2>Message: {message}</h2>
      <input type="button" value="Say Hello!" onClick={() => {
        socket?.send('Hello');
      }} />
    </div>
  );
}
