local lg = love.graphics

local colors = {
  [1] = {0, 184, 148},
  [2] = {0, 206, 201},
  [3] = {9, 132, 227},
  [4] = {108, 92, 231},
  [5] = {225, 112, 85},
}

function createTimeline(file, title)
  local timeline = {
    title = title,
    data = {},
  }
  local line = file:read()
  while (line ~= '+' and line ~= nil) do
    local label
    local intervals = {}
    local j = 1
    for field in line:gmatch('([^,]+)') do
      if j == 1 then
        label = field
      else
        local startTime, endTime = field:match('([^:]+):([^:]+)') 
        intervals[#intervals + 1] = {startTime, endTime}
      end
        j = j + 1
    end
    timeline.data[#timeline.data + 1] = {
      label = label,
      color = colors[#timeline.data + 1],
      time = intervals,
    }
    line = file:read()
  end
  return timeline
end

function createTimelines()
  local timelines = {}
  local file = io.open('results.csv', 'r+')
  local ct = 1
  while (true) do
    local line = file:read()
    if(line == nil) then
      break
    end
    local timeline = createTimeline(file, line)
    timelines[#timelines + 1] = timeline
  end
  file:close()
  return timelines
end

local timelines = createTimelines()
local currentTimeline = 0

local chartData = {
  x = 55,
  y = 100,
  width = 720,
  height = 400,
  timeq = 10,
  scale = 5,
}
-- scale = 1 unit = x pixels

local function norm(rgb)
  return {rgb[1] / 255, rgb[2] / 255, rgb[3] / 255}
end

local function renderChart(chart, timeline)
  local x = chart.x
  local y = chart.y
  local width = chart.width
  local height = chart.height
  local timeq = chart.timeq
  local scale = chart.scale

  lg.line(x, y, x, y + height)
  lg.line(x, y + height, x + width, y + height)

  local labelHeight = height / (#timeline.data)
  local titleWidth = lg.getFont():getWidth(timeline.title)
  lg.print(timeline.title, (chart.x + chart.width * 0.5) - titleWidth * 0.5, 50)

  lg.setColor(0, 0, 0, 0.15)
  for i = 1, math.ceil(width / (timeq * scale)) do
    local ix = x + (i * timeq * scale)
    local iy = y + height
    lg.line(ix, y, ix, iy)
    lg.setColor(0, 0, 0, 1)
    lg.print(i * timeq, ix - 10, iy)
    lg.setColor(0, 0, 0, 0.15)
  end
  lg.setColor(0, 0, 0, 1)

  for i, v in ipairs(timeline.data) do
    local py = chart.y + ((i - 1) * labelHeight)
    lg.print(v.label, chart.x - 25, py + 15)
    lg.setColor(norm(v.color or {0, 0, 0}))
    for i, vv in ipairs(v.time) do
      local tx = vv[1];
      local tl = vv[2];
      lg.rectangle('fill', x + (tx * scale), py, (tl - tx) * scale, labelHeight * 0.5)
    end
    lg.setColor(0, 0, 0)
  end
end

function love.load()
  lg.setBackgroundColor(1, 1, 1)
  love.window.setTitle('Scheduler Gantt Charts')
end

function love.draw()
  renderChart(chartData, timelines[currentTimeline + 1])
end

function love.keypressed(key)
  local amount = (key == 'left') and -1 or ((key == 'right') and 1 or 0)
  local scale = (key == 'up') and 1 or ((key == 'down') and -1 or 0)
  currentTimeline = (currentTimeline + amount) % #timelines
  chartData.scale = math.min(math.max(chartData.scale + scale, 1), 20)
  if (key == 'c') then
    lg.captureScreenshot(timelines[currentTimeline + 1].title .. '.png')
  end
end
