$baseUrl = "https://cdn.jsdelivr.net/gh/oakmac/chessboardjs@1.0.0/website/img/chesspieces/wikipedia"

$pieces = @(
    "wK", "wQ", "wR", "wB", "wN", "wP",
    "bK", "bQ", "bR", "bB", "bN", "bP"
)

$outputDir = Join-Path $PSScriptRoot "assets\pieces"

New-Item `
    -ItemType Directory `
    -Path $outputDir `
    -Force | Out-Null

foreach ($piece in $pieces)
{
    $url = "$baseUrl/$piece.png"
    $outputPath = Join-Path $outputDir "$piece.png"

    Write-Host "Downloading $piece..."

    try
    {
        Invoke-WebRequest `
            -Uri $url `
            -OutFile $outputPath `
            -UseBasicParsing

        $file = Get-Item $outputPath

        if ($file.Length -eq 0)
        {
            Remove-Item $outputPath -Force
            Write-Host "Failed: empty file for $piece"
        }
        else
        {
            Write-Host "Saved: $outputPath"
        }
    }
    catch
    {
        Write-Host "Failed $piece : $($_.Exception.Message)"
    }
}

Write-Host "Finished."