# Wokwi MCP Server Configuration

This directory contains the MCP (Model Context Protocol) server configuration for integrating Wokwi CLI with your AI agent.

## Overview

The `servers.json` file configures the Wokwi MCP server, which allows your AI agent to:
- Control Wokwi simulations programmatically
- Deploy and manage projects
- Interact with simulated devices
- Run builds and simulations via the Wokwi API

## Setup Instructions

### 1. Install Wokwi CLI

The Wokwi CLI is required to run the MCP server. It is available as a standalone binary.

**Windows (already installed):**
- Located at: `C:\Users\targauer\bin\wokwi-cli.exe`
- Verify with: `wokwi-cli --version`

**macOS / Linux (download manually):**
```bash
# Download from https://github.com/wokwi/wokwi-cli/releases
# Or via Homebrew (if available):
brew install wokwi-cli
```

### 2. Get your Wokwi CLI Token

1. Go to https://wokwi.com and sign in to your account
2. Navigate to your account settings (usually found in profile/preferences)
3. Look for "API Keys", "Tokens", or "CLI Token" section
4. Create a new token or copy an existing one
5. Copy the token value (it will look like: `ghp_xxxxxxxxxxxxxxxxxxxxx` or similar)

**Important:** Keep this token private! Do not commit it to the repository.

### 3. Set the Token in Your Environment

Choose one of the following methods:

#### Option A: Export as Environment Variable (Recommended for Local Development)

**Bash / Git Bash / WSL / Linux / macOS:**
```bash
export WOKWI_CLI_TOKEN="your_token_here"
```

**PowerShell (Windows):**
```powershell
$env:WOKWI_CLI_TOKEN = "your_token_here"
```

**Command Prompt (Windows):**
```cmd
set WOKWI_CLI_TOKEN=your_token_here
```

**To make it permanent (Windows):**
1. Press `Win + X` → Settings
2. Search for "Environment Variables"
3. Click "Edit the system environment variables"
4. Click "Environment Variables" button
5. Under "User variables", click "New"
6. Variable name: `WOKWI_CLI_TOKEN`
7. Variable value: `your_token_here` (paste your actual token)
8. Click OK and restart your terminal

#### Option B: Via AI Agent / MCP Client Configuration

If your MCP client supports input variables, it may prompt you for `wokwi-cli-token` when the server starts. Follow the prompt and enter your token.

### 4. Test the MCP Server

With the `WOKWI_CLI_TOKEN` environment variable set, run:

```bash
wokwi-cli mcp
```

**Expected output:**
```
Wokwi CLI v0.18.3 (...)
Wokwi MCP Server started
```

The MCP server is now listening on stdio and ready to accept MCP protocol messages. The AI agent will spawn this process automatically when needed.

### 5. Verify with Your AI Agent

If you're using an MCP client (like Claude Desktop, VS Code MCP extension, or a custom MCP host):

1. Ensure `WOKWI_CLI_TOKEN` is set in your environment
2. Start your AI agent / MCP client
3. Check the MCP logs for successful connection to the Wokwi server
4. The agent should be able to execute Wokwi commands programmatically

## Usage Examples

Once the MCP server is running, your AI agent can:

- Create and configure Wokwi simulations
- Deploy your DarkishTower project to Wokwi
- Control simulations (start, stop, pause)
- Query simulation state
- Access simulation outputs and debugging info

Example agent prompts:
> "Import my DarkishTower GitHub repo into Wokwi and start a simulation"
> "Deploy the sketch to Wokwi and show me the serial output"
> "Run the DarkishTower game in Wokwi with the -DWOKWI build flag"

## Troubleshooting

### "Command not found: wokwi-cli"
- Ensure Wokwi CLI is installed and in your PATH
- Verify the path: `which wokwi-cli` (Unix) or `where wokwi-cli` (Windows)
- If not in PATH, use the full path: `/c/Users/targauer/bin/wokwi-cli.exe mcp`

### "WOKWI_CLI_TOKEN not set or invalid"
- Verify the token is exported: `echo $WOKWI_CLI_TOKEN` (Unix) or `echo %WOKWI_CLI_TOKEN%` (Windows)
- Double-check your token value on https://wokwi.com
- Ensure the token has not expired or been revoked
- Create a new token if needed

### MCP server won't start
- Check for error messages in the console output
- Ensure your network connection is stable
- Try running with verbose logging: `wokwi-cli mcp --verbose` (if supported)

### Agent can't connect to MCP server
- Verify the environment variable is set before starting the agent
- Check the agent's MCP configuration and logs
- Ensure `servers.json` is in the `.mcp/` directory
- Confirm the `WOKWI_CLI_TOKEN` matches your account token

## Security Notes

- **Never commit your token to the repository.** The `.gitignore` in the repo root should prevent accidental commits.
- Use environment variables or secret management systems to store tokens.
- Rotate your token periodically if you suspect compromise.
- For CI/CD pipelines, use secret management (GitHub Secrets, GitLab CI/CD variables, etc.) to inject the token.

## Files in This Directory

- `servers.json` — MCP server configuration for Wokwi CLI
- `README.md` — This file; setup and usage guide

## Further Reading

- Wokwi Documentation: https://docs.wokwi.com
- Wokwi CLI Repository: https://github.com/wokwi/wokwi-cli
- Model Context Protocol (MCP): https://modelcontextprotocol.io

## Support

For issues with Wokwi CLI or the MCP server:
- Check Wokwi GitHub issues: https://github.com/wokwi/wokwi-cli/issues
- Visit Wokwi community: https://wokwi.com/
- Read the project README: https://github.com/mighty-bean/DarkishTower

---

**Last Updated:** November 12, 2025
