import { jsx as _jsx, jsxs as _jsxs } from "/home/caubut/.local/share/ags/gtk3/jsx-runtime";
import { App } from "astal/gtk3";
import { Variable, GLib, bind } from "astal";
import { Astal, Gtk, Gdk } from "astal/gtk3";
import Hyprland from "gi://AstalHyprland";
import Mpris from "gi://AstalMpris";
import Battery from "gi://AstalBattery";
import Wp from "gi://AstalWp";
import Network from "gi://AstalNetwork";
import Tray from "gi://AstalTray";
function SysTray() {
    const tray = Tray.get_default();
    return _jsx("box", { children: bind(tray, "items").as(items => items.map(item => {
            if (item.iconThemePath)
                App.add_icons(item.iconThemePath);
            const menu = item.create_menu();
            return _jsx("button", { tooltipMarkup: bind(item, "tooltipMarkup"), onDestroy: () => menu?.destroy(), onClickRelease: self => {
                    menu?.popup_at_widget(self, Gdk.Gravity.SOUTH, Gdk.Gravity.NORTH, null);
                }, children: _jsx("icon", { gIcon: bind(item, "gicon") }) });
        })) });
}
function Wifi() {
    const { wifi } = Network.get_default();
    return _jsx("icon", { tooltipText: bind(wifi, "ssid").as(String), className: "Wifi", icon: bind(wifi, "iconName") });
}
function AudioSlider() {
    const speaker = Wp.get_default()?.audio.defaultSpeaker;
    return _jsxs("box", { className: "AudioSlider", css: "min-width: 140px", children: [_jsx("icon", { icon: bind(speaker, "volumeIcon") }), _jsx("slider", { hexpand: true, onDragged: ({ value }) => speaker.volume = value, value: bind(speaker, "volume") })] });
}
function BatteryLevel() {
    const bat = Battery.get_default();
    return _jsxs("box", { className: "Battery", visible: bind(bat, "isPresent"), children: [_jsx("icon", { icon: bind(bat, "batteryIconName") }), _jsx("label", { label: bind(bat, "percentage").as(p => `${Math.floor(p * 100)} %`) })] });
}
function Media() {
    const mpris = Mpris.get_default();
    return _jsx("box", { className: "Media", children: bind(mpris, "players").as(ps => ps[0] ? (_jsxs("box", { children: [_jsx("box", { className: "Cover", valign: Gtk.Align.CENTER, css: bind(ps[0], "coverArt").as(cover => `background-image: url('${cover}');`) }), _jsx("label", { label: bind(ps[0], "title").as(() => `${ps[0].title} - ${ps[0].artist}`) })] })) : ("Nothing Playing")) });
}
function Workspaces() {
    const hypr = Hyprland.get_default();
    return _jsx("box", { className: "Workspaces", children: bind(hypr, "workspaces").as(wss => wss
            .sort((a, b) => a.id - b.id)
            .map(ws => (_jsx("button", { className: bind(hypr, "focusedWorkspace").as(fw => ws === fw ? "focused" : ""), onClicked: () => ws.focus(), children: ws.id })))) });
}
function FocusedClient() {
    const hypr = Hyprland.get_default();
    const focused = bind(hypr, "focusedClient");
    return _jsx("box", { className: "Focused", visible: focused.as(Boolean), children: focused.as(client => (client && _jsx("label", { label: bind(client, "title").as(String) }))) });
}
function Time({ format = "%H:%M - %A %e." }) {
    const time = Variable("").poll(1000, () => GLib.DateTime.new_now_local().format(format));
    return _jsx("label", { className: "Time", onDestroy: () => time.drop(), label: time() });
}
export default function Bar(monitor) {
    const anchor = Astal.WindowAnchor.TOP
        | Astal.WindowAnchor.LEFT
        | Astal.WindowAnchor.RIGHT;
    return _jsx("window", { className: "Bar", gdkmonitor: monitor, exclusivity: Astal.Exclusivity.EXCLUSIVE, anchor: anchor, children: _jsxs("centerbox", { children: [_jsxs("box", { hexpand: true, halign: Gtk.Align.START, children: [_jsx(Workspaces, {}), _jsx(FocusedClient, {})] }), _jsx("box", { children: _jsx(Media, {}) }), _jsxs("box", { hexpand: true, halign: Gtk.Align.END, children: [_jsx(SysTray, {}), _jsx(Wifi, {}), _jsx(AudioSlider, {}), _jsx(BatteryLevel, {}), _jsx(Time, {})] })] }) });
}
//# sourceMappingURL=Bar.js.map