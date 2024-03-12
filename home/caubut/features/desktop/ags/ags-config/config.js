import { Bar } from "./Bar.js"
import { applauncher } from "./AppLauncher.js"
// import { iconbrowser } from "./IconBrowser.js"

export default App.config({
    style: "./style.css",
    windows: [
        Bar(),
        applauncher,
        // iconbrowser,

        // you can call it, for each monitor
        // Bar(0),
        // Bar(1)
    ],
});
