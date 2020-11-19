#include <telemetry_codec.h>
#include <stdio.h>

/* Encode function */
QCBORError telemetry_codec_encode(const telemetry_data_t *p_data, uint8_t *p_buf, size_t len, size_t *p_size)
{

    // Setup of the goods
    UsefulBuf buf = {
        .ptr = p_buf,
        .len = len};
    QCBOREncodeContext ec;
    QCBOREncode_Init(&ec, buf);

    /* Create over-arching map */
    QCBOREncode_OpenMap(&ec);

    /* Add the version string */
    UsefulBufC data = {
        .ptr = p_data->version.bytes,
        .len = p_data->version.size};
    QCBOREncode_AddBytesToMapN(&ec, telemetry_version_pos, data);

    /* Add the rssi */
    QCBOREncode_AddInt64ToMapN(&ec, telemetry_rssi_pos, p_data->rssi);

    /* Close the map*/
    QCBOREncode_CloseMap(&ec);

    /* Finish !*/
    return QCBOREncode_FinishGetSize(&ec, p_size);
}

/* Decode function */
int telemetry_codec_decode(telemetry_data_t *p_data, const uint8_t *p_buf, size_t len)
{
    /* Setup of the goods */
    UsefulBufC buf = {
        .ptr = p_buf,
        .len = len};
    QCBORDecodeContext dc;
    QCBORItem item;

    /* Clear memory contents before work */
    memset(p_data, 0, sizeof(telemetry_data_t));

    /* Start decode process */
    QCBORDecode_Init(&dc, buf, QCBOR_DECODE_MODE_NORMAL);

    /* Get the next item. It should be a map with our data! */
    QCBORDecode_GetNext(&dc, &item);
    if (item.uDataType != QCBOR_TYPE_MAP)
    {
        printf("Expected CBOR map structure.\n");
        return -1;
    }

    /* Need to set this in stone before iteration*/
    const uint8_t count = item.val.uCount;

    /* Iterate through all the entries in the map */
    for (int i = 0; i < count; i++)
    {

        /* Get the next item in the map */
        QCBORDecode_GetNext(&dc, &item);

        switch (item.label.int64)
        {
        case telemetry_version_pos:
            if (item.val.string.len <= sizeof(p_data->version.bytes))
            {
                /* Copy over contents */
                memcpy(p_data->version.bytes, item.val.string.ptr, item.val.string.len);
                p_data->version.size = item.val.string.len;
            }
            else
            {
                printf("QCBOR decode input overflow!");
            }
            break;
        case telemetry_rssi_pos:
            /* Copy over RSSI */
            p_data->rssi = (int32_t)item.val.int64;
            break;
        default:
            break;
        }
    }

    return 0;
}