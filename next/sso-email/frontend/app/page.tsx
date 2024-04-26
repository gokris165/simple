"use client";

import { useUser } from "@auth0/nextjs-auth0/client";
import Hotel from "./hotel/page";
import { Button } from "@mantine/core";
import "./globals.css";

export default function Home() {
  const { user, error, isLoading } = useUser();

  if (user) {
    return <Hotel user_name={user.name} user_email={user.email} />;
  } else {
    return (
      <>
        <a href="api/auth/login">
          <div className="center-login-button">
            <Button size="xl" variant="filled">
              Login
            </Button>
          </div>
        </a>
      </>
    );
  }
}
