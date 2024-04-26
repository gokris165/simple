import { UserProvider } from "@auth0/nextjs-auth0/client";
import "@mantine/core/styles.css";
import { DEFAULT_THEME, MantineProvider } from "@mantine/core";

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <UserProvider>
        <MantineProvider theme={DEFAULT_THEME} forceColorScheme="dark">
          <body>{children}</body>
        </MantineProvider>
      </UserProvider>
    </html>
  );
}
