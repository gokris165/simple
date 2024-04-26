import { Box, Button, Image, Alert } from "@mantine/core";
import "../globals.css";

type HotelProps = {
  user_name: string | undefined | null;
  user_email: string | undefined | null;
};

export default function Hotel({ user_name, user_email }: HotelProps) {
  async function bookNowButton() {
    fetch("http://localhost:8000/send_email", {
      method: "POST",
      mode: "no-cors",
      headers: {
        "Content-Type": "application/json",
        accept: "application/json",
      },
      body: JSON.stringify({ user_email: user_email, user_name: user_name }),
    });
    window.alert(`An email confirmation has been sent to ${user_email}`);
  }

  return (
    <>
      <header className="top-header">
        <div className="header-left">
          <p></p>
        </div>
        <div className="header-middle">
          <p>{`Welcome ${user_name}`}</p>
        </div>
        <div className="header-right">
          <a href="api/auth/logout">
            <Button className="logout-button" size="md" variant="filled">
              Logout
            </Button>
          </a>
        </div>
      </header>

      <section className="home-body">
        <div className="hotel-image">
          <Box>
            <Image src="/hotel-image.jpg" radius={20}></Image>
          </Box>
        </div>
        {/* <div className="hotel-amenities">
          <Box>
            <p>AMENITIES</p>
          </Box>
        </div> */}
        <div className="hotel-booking">
          <Button
            onClick={() => {
              bookNowButton();
            }}
            size="xm"
          >
            Book Now!
          </Button>
        </div>
      </section>
    </>
  );
}
